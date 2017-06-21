#include "Algorithm.h"
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <tgmath.h>

using namespace std;


#define ERROR -1
Algorithm::Algorithm(int blocks_num , double f_old , double f_new  ,cache_algo_t algoName):blockNum(blocks_num) , algoName
        (algoName)
{
    //block size call
    struct stat fi;
    stat("/tmp", &fi);
    blksize = fi.st_blksize;
    pathToVectorOfBlocks  =  new std::unordered_map<std::string, std::vector<bool>>();
    fidToPath = new std::unordered_map<int, std::string>();
    oldPartitionFinishLocation = (int)std::floor(blocks_num * f_old);
    newPartitionFinishLocation = (int)std::floor(blocks_num * f_new);
    hitsNum = 0;
    missNum = 0;

}

const vector<Block *> &Algorithm::getVectorOfBlocks() const {
    return vectorOfBlocks;
}

Algorithm::~Algorithm() {
    pathToVectorOfBlocks->clear();
    fidToPath->clear();
    delete (pathToVectorOfBlocks);
    delete (fidToPath);
    pathToVectorOfBlocks = nullptr;
    fidToPath = nullptr;
    for (auto iter = vectorOfBlocks.begin(); iter != vectorOfBlocks.end(); ++iter) {
        delete (*iter);
    }
}

const cache_algo_t &Algorithm::getAlgoName() const {
    return algoName;
}

int Algorithm::programOpen(std::string pathName) {
    unsigned long fileLength;
    int fid = open(pathName.c_str(), O_RDONLY|O_SYNC|O_DIRECT);
    if(fid  == ERROR)
    {
        return ERROR;
    }
    std::ifstream is(pathName, std::ifstream::ate | std::ifstream::binary);
    if(is)
    {
        fileLength = (unsigned long)is.tellg();
    } else
    {
        return ERROR;
    }
    unsigned long  numOfMaxBlock = ((fileLength + blksize  - 1) / blksize);//To round up the result
    (*fidToPath)[fid] = pathName;
    std::vector<bool> fileBlocks(numOfMaxBlock , false);
    (*pathToVectorOfBlocks)[pathName] = fileBlocks;
    return fid;

}


int Algorithm::CachePread(int file_id, void *buf, size_t count, off_t offset)
{
    if (count == 0){
        return 0;
    }
    if ( fidToPath->find(file_id) == fidToPath->end() )
    {
        return -1;
    }
    void *buffer;
    string  a;
    string currentData;
    std::string path = (*fidToPath)[file_id];
    string dataToReturn;
    bool isAllocated = false;

    int startBlock , currentBlock , endBlock;
    startBlock =(int)(offset/blksize);
    currentBlock = startBlock;
    endBlock = (int)((offset + count - 1) / blksize) + 1;
    for (currentBlock; currentBlock < endBlock ; ++currentBlock)
    {
        if (currentBlock < ((*pathToVectorOfBlocks)[path].size()))
        {
            if(!isInCache(path, currentBlock))
            {
                buffer = aligned_alloc(blksize , blksize);
                isAllocated = true;
                ssize_t readFile = pread(file_id, buffer, blksize, (currentBlock*blksize));
                if (readFile < 0)
                {
                    return ERROR;
                }
                Block * block  = new Block(buffer, path, currentBlock);
                ((*pathToVectorOfBlocks)[path])[currentBlock] = true;
                addBlockToCache(block);
                MissNumPlus();
            } else
            {
                int counter = 0;
                for (auto i = vectorOfBlocks.begin(); i != vectorOfBlocks.end(); ++i )
                {
                    if (!path.compare((*i)->getFilePath()))
                    {
                        if (currentBlock == (*i)->getBlockNum())
                        {
                            buffer = (*i)->getMemory();
                            if (counter < newPartitionFinishLocation)
                            {
                                (*i)->upFreq();
                            }
                            HitsNumPlus();
                            break;
                        }
                    }
                    counter++;
                }
                Block *blockToAppend = vectorOfBlocks[counter];
                vectorOfBlocks.erase(std::remove(vectorOfBlocks.begin(), vectorOfBlocks.end(), blockToAppend)
                        , vectorOfBlocks.end());
                vectorOfBlocks.push_back(blockToAppend);


            }
            currentData = ((char *)buffer);
            currentData = currentData.substr(0,blksize);
            if (currentBlock == (endBlock - 1)){
                if ((count+offset )%blksize){
                    currentData = currentData.substr(0,((count+offset )%blksize));
                }else{
                    currentData = currentData.substr(0,blksize);
                }
            }
            if (currentBlock == startBlock)
            {
                currentData = currentData.substr(((unsigned long)offset)%blksize , currentData.size());
            }
            dataToReturn += currentData;
        } else {
            break;
        }
    }
    void* toBuf = (void *)dataToReturn.c_str();
    memcpy(buf , toBuf , dataToReturn.size());
    return (int)dataToReturn.size();
}

bool Algorithm::isInCache(std::string filePath, int blockNum)
{
    if ( pathToVectorOfBlocks->find(filePath) == pathToVectorOfBlocks->end())
    {
        return false;
    }else
    {
        return (*pathToVectorOfBlocks)[filePath][blockNum];
    }
}



void Algorithm::addBlockToCache(Block *block)
{
//    cout << "Before change: " << endl;
//    for ( auto i = vectorOfBlocks.rbegin(); i != vectorOfBlocks.rend(); i++ ) {
//        std::cout << (*i)->getBlockNum();
//        std::cout << " - " << (*i)->getFreq() << std::endl;
//
//    }

    auto endOfOld = vectorOfBlocks.begin() + oldPartitionFinishLocation;
    if (vectorOfBlocks.size() >= blockNum)
    {
        vector<Block*>::iterator itemToDelete;
        auto min = vectorOfBlocks.begin();
        for ( auto i = vectorOfBlocks.begin(); i != endOfOld; i++ ) {
            if ((*i)->getFreq() < (*min)->getFreq()){
                min = i;
                break;
            }
        }

        string filePath = (*min)->getFilePath();
        int currentBlockNum = (*min)->getBlockNum();
        (*pathToVectorOfBlocks)[filePath][currentBlockNum] = false;
//        cout << "Item to delete " << (*min)->getBlockNum() << endl;

        void* buffer = (*min)->getMemory();
        free(buffer);
        delete (*min);
        vectorOfBlocks.erase(min);
    }
    (*pathToVectorOfBlocks)[block->getFilePath()][block->getBlockNum()] = true;
    vectorOfBlocks.push_back(block);
//    cout << "After change: " << endl;
//    for ( auto i = vectorOfBlocks.rbegin(); i != vectorOfBlocks.rend(); i++ ) {
//        std::cout << (*i)->getBlockNum();
//        std::cout << " - " << (*i)->getFreq() << std::endl;
//    }

}

std::vector<Block *> Algorithm::arrangedVec() {
    if(algoName == FBR or algoName == LRU)
    {
        return vectorOfBlocks;
    }
    else
    {
        std::vector<Block *> sortVec = vectorOfBlocks;
        std::sort(sortVec.begin(), sortVec.end());
        return sortVec;
    }
}

int Algorithm::closeFile(int fileId)
{
    if (fidToPath->find(fileId) == fidToPath->end())
    {
        return ERROR;
    }
    else
    {
        string path = fidToPath->at(fileId);
        int fileClosing = close(fileId);
        if (fileClosing == -1)
        {
            return ERROR;
        }
        fidToPath->erase(fileId);

        for (auto iter = fidToPath->begin() ; iter != fidToPath->end() ;++iter)
        {
//            std::cout<<"in close "<<std::endl;
//            std::cout<<"check with path: "<<path<<std::endl;

//            std::cout<<"fid num "<<(*iter).first<<" is ile path "<<(*iter).second<<std::endl;
            if (path.compare((*iter).second) == 0)
            {
//                std::cout<<"path.compare((*iter).second)"<<path.compare((*iter).second)<<std::endl;
                return 0;
            }
//            std::cout<<"path.compare((*iter).second)"<<path.compare((*iter).second)<<std::endl;

        }
//        std::cout<<"earse"<<std::endl;

        pathToVectorOfBlocks->erase(path);
        return 0;
    }
}

int Algorithm::getHitsNum() const
{
    return hitsNum;
}

int Algorithm::getMissNum() const
{
    return missNum;
}

void Algorithm::HitsNumPlus()
{
    hitsNum++;
}

void Algorithm::MissNumPlus()
{
    missNum++;
}

unordered_map<string, vector<bool, allocator<bool>>> *Algorithm::getPathToVectorOfBlocks() const {
    return pathToVectorOfBlocks;
}


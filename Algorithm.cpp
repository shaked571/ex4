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
    void *buffer;
    string currentData;
    std::string path = (*fidToPath)[file_id];
    string dataToReturn;
    bool isAllocated = false;

    int startBlock , currentBlock , endBlock;
    startBlock =(int)(offset/blksize);
    currentBlock = startBlock;
    endBlock = (int)((offset + count) / blksize) + 1;
    for (currentBlock; currentBlock < endBlock ; ++currentBlock)
    {
        if(!isInCache(path, currentBlock))
        {
            buffer = aligned_alloc(blksize , blksize);
            isAllocated = true;
            pread(file_id, buffer, blksize, (currentBlock*blksize));
            Block * block  = new Block(buffer, path, currentBlock);
            ((*pathToVectorOfBlocks)[path])[currentBlock] = block;
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
                        break;
                    }
                }
                counter++;
            }
            HitsNumPlus();
        }
        currentData = ((char *)buffer);
        if (currentBlock == (endBlock - 1)){
            currentData = currentData.substr(0, (count+offset)%blksize);
        }
        if (currentBlock == startBlock){
            currentData = currentData.substr(((unsigned long)offset)%blksize , currentData.size());
        }
        dataToReturn += currentData;
    }

    void* toBuf = (void *)currentData.c_str();
    memcpy(buf , toBuf , currentData.size());
    if (isAllocated){
        free(buffer);
    }
    return (int)currentData.size();
}

bool Algorithm::isInCache(std::string filePath, int blockNum)
{
    return (*pathToVectorOfBlocks)[filePath][blockNum];
}



void Algorithm::addBlockToCache(Block *block)
{
    vector<Block*>::iterator endOfOld = vectorOfBlocks.begin() + oldPartitionFinishLocation;
    if (vectorOfBlocks.size() >= blockNum)
    {
        auto min = std::min_element(vectorOfBlocks.begin(), endOfOld , [](Block *a, Block * b)
        { return a->getFreq() < b->getFreq(); });
        string filePath = (*min)->getFilePath();
        int blockNum = (*min)->getBlockNum();
        (*pathToVectorOfBlocks)[filePath][blockNum] = false;
        delete(*min);
        vectorOfBlocks.erase(min);
    }
    (*pathToVectorOfBlocks)[block->getFilePath()][block->getBlockNum()] = true;
    vectorOfBlocks.push_back(block);

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





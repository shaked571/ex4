//
// Created by shaked571 on 6/10/17.
//

#include <stdlib.h>
#include <unistd.h>
#include "LruAlgorithm.h"

LruAlgorithm::LruAlgorithm(int blocks_num) :Algorithm(blocks_num)
{

}


/**
   Read data from an open file.

   Read should return exactly the number of bytes requested except
   on EOF or error. For example, if you receive size=100, offset=0,
   but the size of the file is 10, you will initialize only the first
   ten bytes in the buff and return the number 10.

   In order to read the content of a file in CacheFS,
   We decided to implement a function similar to POSIX's pread, with
   the same parameters.

 Returned value:
    In case of success:
		Non negative value represents the number of bytes read.
		See more details above.

 	In case of failure:
		Negative number.
		A failure will occur if:
			1. a system call or a library function fails (e.g. pread).
			2. invalid parameters
				a. file_id is valid if"f it was returned by
			       CacheFS_open, and it wasn't already closed.
				b. buf is invalid if it is NULL.
				c. offset is invalid if it's negative
				   [Note: offset after the end of the file is valid.
				    In this case, you need to return zero,
				    like posix's pread does.]
				[Note: any value of count is valid.]
 */
int LruAlgorithm::ChachePread(int file_id, void *buf, size_t count, off_t offset)
{

    const int key = file_id;
    std::string fullPath;
    fullPath = fidToPath->at(key);
    void* buffer = aligned_alloc(blksize , blksize);
    std::cout << pread(file_id, buffer, blksize, 0) << std::endl;
    std::cout << (char*)buffer << std::endl;
    if(vectorOfBlocks.size() < blockNum)
    {

    }
    return 0;
}

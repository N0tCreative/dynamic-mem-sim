/* memory method file
 * Jerad Alexander Arnold
 * 1008362
 * jerad@uoguelph.ca
 * 2019-09-29
 */

#include "ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

union temp{
  int i;
  int valid;
};
/* creats a file and writes initial data into file ***completed*/
int ds_create (char * filename, long size){
    union temp tmp;
    int null =0;
    ds_file.fp = fopen(filename, "wb+");
    if (ds_file.fp==NULL){
      return -1;
    }
    for(tmp.i = 0; tmp.i < MAX_BLOCKS; tmp.i++){
      ds_file.block[tmp.i].start =0;
      ds_file.block[tmp.i].length =0;
      ds_file.block[tmp.i].alloced =0;
    }
    ds_file.block[0].length = size;
    tmp.valid = fwrite((void*)(ds_file.block), sizeof(struct ds_blocks_struct), MAX_BLOCKS, ds_file.fp);
    if (tmp.valid < MAX_BLOCKS){
      return 1;
    }
    for(tmp.i = 0; tmp.i < size; tmp.i++){
      null = fwrite((void*) &null, 1, 1, ds_file.fp);
      if(null != 1){
        return 2;
      }
    }
    fclose(ds_file.fp);
    return 0;

}

/*copys from file into ds_file ****completed*/
int ds_init(char * filename){
    union temp tmp2;
    ds_counts.reads =0;
    ds_counts.writes =0;

    ds_file.fp = fopen(filename, "rb+");
    if (ds_file.fp==NULL){
      return -1;
    }
    fseek(ds_file.fp, 0, SEEK_SET);
    for(tmp2.i=0;tmp2.i<MAX_BLOCKS;tmp2.i++){
		fread(&(ds_file.block[tmp2.i]), sizeof(struct ds_blocks_struct), 1, ds_file.fp);
	}
    return 0;
}

/*finds amount bits in memory and allocates it then sets the next free memory to take up the left over space ****completed*/
long ds_malloc( long amount){
	union temp tmp;
	union temp tmp2;
	long origLength;
	/*checks all blocks to see if there is one with enough space to store data*/
	for(tmp.i =0; tmp.i < MAX_BLOCKS;tmp.i++){
		/*if a block has enough space it checks to see if there is a block that can be appended to the end to take the blank space*/
		if(ds_file.block[tmp.i].alloced == 0 && ds_file.block[tmp.i].length >= amount){
			ds_file.block[tmp.i].alloced = 1;
			origLength = ds_file.block[tmp.i].length;
			ds_file.block[tmp.i].length = amount;
			for(tmp2.i =0; tmp2.i < MAX_BLOCKS;tmp2.i++){
				if(ds_file.block[tmp2.i].length == 0 && tmp.i !=tmp2.i){
					ds_file.block[tmp2.i].start = ds_file.block[tmp.i].start + amount;
					ds_file.block[tmp2.i].length = origLength - amount;
					ds_file.block[tmp2.i].alloced = 0;
					break;
				}
			}
			return ds_file.block[tmp.i].start;
			
			break;
		}
	}
	return -1;
}

/*frees memory malloc'd with ds_malloc****completed*/
void ds_free(long start){
	union temp tmp;
	for(tmp.i =0; tmp.i < MAX_BLOCKS; tmp.i++){
		if(ds_file.block[tmp.i].start == start){
			ds_file.block[tmp.i].alloced = 0;
			break;
		}
	}
}

/*reads from file****completed*/
void *ds_read( void *ptr, long start, long bytes){
	union temp tmp;
	fseek(ds_file.fp, start + (sizeof(struct ds_blocks_struct)*MAX_BLOCKS), SEEK_SET);
	tmp.valid = fread( ptr, bytes, 1, ds_file.fp);
	if(tmp.valid ==0){
		return NULL;
	}
	else{
		ds_counts.reads++;
		return ptr;
	}
}

/*writes to file****completed*/
long ds_write( long start, void *ptr, long bytes){
	union temp tmp;
	fseek(ds_file.fp, start + (sizeof(struct ds_blocks_struct)*MAX_BLOCKS), SEEK_SET);
	tmp.valid = fwrite( ptr, bytes, 1, ds_file.fp);
	if(tmp.valid ==0){
		return -1;
	}
	else{
		ds_counts.writes++;
		return start;
	}
}

/*writes block array to file and then closes file****completed*/
int ds_finish(){
	union temp tmp;

	/*for(tmp.i =0; tmp.i < 15;tmp.i++){
		printf("%d: %ld, %ld, %d\n", tmp.i, ds_file.block[tmp.i].start, ds_file.block[tmp.i].length, ds_file.block[tmp.i].alloced);
	}*/
	fseek(ds_file.fp, 0, SEEK_SET);
    for(tmp.i=0;tmp.i<MAX_BLOCKS; tmp.i++){
		fwrite(&(ds_file.block[tmp.i]), sizeof(struct ds_blocks_struct), 1, ds_file.fp);
	}
    /*if(tmp.valid <MAX_BLOCKS){ doesnt work properly
        printf("error writing to file\n");
        return 1;
    }*/
    fclose(ds_file.fp);
    printf("reads: %d\n", ds_counts.reads);
    printf("writes: %d\n", ds_counts.writes);
    return 0;
}

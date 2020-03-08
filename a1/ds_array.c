/* array method file
 * Jerad Alexander Arnold
 * 1008362
 * jerad@uoguelph.ca
 * 2019-09-29
 */

#include "ds_array.h"
#include "ds_memory.h"


long elements;

int ds_create_array(){
	int valid=0;
	long memory;
	valid = ds_init("array.bin");
	if(valid !=0){
		return -1;
	}
	memory = ds_malloc(sizeof(long));
	ds_write(memory, &elements, sizeof(long));
	ds_malloc(sizeof(int)*MAX_ELEMENTS);
	
	ds_finish();
	return 0;
}

int ds_init_array(){
	int valid;
	valid = ds_init("array.bin");
	if(valid != 0){
		return -1;
	}
	ds_read(&elements, 0, sizeof(long));
	return 0;
}

int ds_replace(int value, long index){
	long result =0;
	if(index > elements){
		return 1;
	}
	else{
		result = ds_write(index * sizeof(int) + sizeof(long), &value, sizeof(int));
	}
	return result;
}

int ds_insert(int value, long index){
	int tmp, tmp2, i, result =0;
	tmp2 = value;
	if(index > elements){
		return -1;
	}
	else{
		for(i=index;i<=elements;i++){
			ds_read(&tmp, i*sizeof(int) + sizeof(long), sizeof(int));
			result = ds_write(i*sizeof(int) + sizeof(long), &tmp2, sizeof(int));
			if(result ==-1){
				
				return result;
			}
			tmp2=tmp;
		}
	}
	elements++;
	return result;
}

int ds_delete(long index){
	int tmp, i, result;
	if(index > elements){
		return -1;
	}
	else{
		for(i=index;i<elements;i++){
			ds_read(&tmp, (i+1)*sizeof(int) + sizeof(long), sizeof(int));
			result = ds_write(i*sizeof(int) + sizeof(long), &tmp, sizeof(int));
			if(result ==-1){
				
				return result;
			}
			
		}
	}
	elements--;
	return result;
}

int ds_swap(long index1, long index2){
	int tmp, tmp2;
	if(index1 > elements || index2 > elements){
		return -1;
	}
	
	ds_read(&tmp, index1 * sizeof(int) + sizeof(long), sizeof(int));
	ds_read(&tmp2, index2 * sizeof(int) + sizeof(long), sizeof(int));
	ds_replace(tmp2, index1);
	ds_replace(tmp, index2);
	return 0;
}

long ds_find(int target){
	int i, value;
	for(i=0; i<elements;i++){
		ds_read(&value, i*sizeof(int) + sizeof(long), sizeof(int));
		if(value == target){
			return (i*sizeof(int) + sizeof(long));
		}
	}
	return -1;
}

int ds_read_elements(char*filename){
	int i =0, tmp=0;
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp ==NULL){
		return -1;
	}
	while(fscanf(fp, "%d\n", &tmp) > 0){
		if(elements == MAX_ELEMENTS){
			return 1;
		}
		else{
			ds_insert(tmp, i);
			i++;
		}
	}
	
	return 0;
}

int ds_finish_array(){
	int result =0;
	ds_write(0, &elements, sizeof(long));
	result =ds_finish();
	elements =0;
	
	return result;
}

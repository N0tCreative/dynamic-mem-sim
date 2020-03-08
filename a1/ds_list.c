/* list method file
 * Jerad Alexander Arnold
 * 1008362
 * jerad@uoguelph.ca
 * 2019-09-29
 */

#include "ds_list.h"
#include "ds_memory.h"

int ds_create_list(){
	int result;
	long start, tmp;
	result =ds_init("list.bin");
	if(result != 0){
		return result;
	}
	start =ds_malloc(sizeof(long));
	if(start ==-1){
		return 3;
	}
	tmp = -1;
	start =ds_write(start, &tmp, sizeof(long));
	if(start ==-1){
		return 4;
	}
	result = ds_finish();
	return 0;
}

int ds_init_list(){
	int result;
	result = ds_init("list.bin");
	return result;
}

int ds_replace(int value, long index){
	struct ds_list_item_struct previous;
	int i;
	long previous_loc=0;
	ds_read(&(previous.next), 0, sizeof(long));
	for(i = index+1; i>0; i--){
		if(previous.next == -1){
			return -1;
		}
		previous_loc = previous.next;
		ds_read(&previous, previous.next, sizeof(struct ds_list_item_struct));
	}
	if(previous_loc ==0){
		return 5;
	}
	previous.item = value;
	ds_write(previous_loc, &previous, sizeof(struct ds_list_item_struct));
	return 0;
}

int ds_insert(int value, long index){
	struct ds_list_item_struct new;
	struct ds_list_item_struct previous;
	int i;
	long previous_loc=0, start;
	/*reads head*/
	ds_read(&(previous.next), 0, sizeof(long));
	/*keep looping untill you reach wanted index*/
	for(i = index; i>0; i--){
		/*if you run out of nodes before you reach the end then throw error*/
		if(previous.next == -1){
			return -1;
		}
		previous_loc = previous.next;
		ds_read(&previous, previous.next, sizeof(struct ds_list_item_struct));
		
	}
	new.item =value;
	new.next = previous.next;
	start = ds_malloc(sizeof(struct ds_list_item_struct));
	previous.next = start;
	ds_write(start, &new, sizeof(struct ds_list_item_struct));
	if(previous_loc ==0){
		ds_write(0, &(previous.next), sizeof(long));
	}
	else{
		ds_write(previous_loc, &(previous), sizeof(struct ds_list_item_struct));
	}	
	return 0;
}

int ds_delete(long index){
	struct ds_list_item_struct new;
	struct ds_list_item_struct previous;
	int i;
	long previous_loc=0, end = -1;
	ds_read(&(previous.next), 0, sizeof(long));
	if(index <0){
		return -1;
	}
	for(i = index; i>0; i--){
		if(previous.next == -1){
			return -1;
		}
		previous_loc = previous.next;
		ds_read(&previous, previous.next, sizeof(struct ds_list_item_struct));
	}
	if(previous.next == -1){
		return 5;
	}
	ds_read(&new, previous.next, sizeof(struct ds_list_item_struct));
	end = new.next;
	ds_free(previous.next);
	previous.next = end;
	if(previous_loc ==0){
		ds_write(0, &(previous.next), sizeof(long));
	}
	else{
		ds_write(previous_loc, &previous, sizeof(struct ds_list_item_struct));
	}
	
	return 0;
}

int ds_swap(long index1, long index2){
	struct ds_list_item_struct node1;
	struct ds_list_item_struct node2;
	int i;
	/*long node1_loc=0, node2_loc=0;*/
	ds_read(&(node1.next), 0, sizeof(long));
	node2.next = node1.next;
	for(i = index1+1; i>0; i--){
		if(node1.next == -1){
			return -1;
		}
		/*node1_loc = node1.next;*/
		ds_read(&node1, node1.next, sizeof(struct ds_list_item_struct));
	}
	for(i = index2+1; i>0; i--){
		if(node2.next == -1){
			return -1;
		}
		/*node2_loc = node2.next;*/
		ds_read(&node2, node2.next, sizeof(struct ds_list_item_struct));
	}
	ds_replace(node1.item, index2);
	ds_replace(node2.item, index1);
	return 0;
}

long ds_find(int target){
	struct ds_list_item_struct previous;
	long previous_loc=0;
	ds_read(&(previous.next), 0, sizeof(long));
	while(previous.next != -1){
		previous_loc = previous.next;
		ds_read(&previous, previous.next, sizeof(struct ds_list_item_struct));
		if(previous.item == target){
			return previous_loc;
		}
	}
	return -1;
}

int ds_read_elements(char*filename){
	int i =0, tmp=0, result;
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp ==NULL){
		return -1;
	}
	while(fscanf(fp, "%d\n", &tmp) > 0){
		result =ds_insert(tmp, i);
		if(result !=0){
			return result;
		}
		i++;
	}
	
	return 0;
}

int ds_finish_list(){
	int result;
	result = ds_finish();
	return result;
}

void print_list(){
	struct ds_list_item_struct node;
	int i =0;
	long loc;
	ds_read(&(node.next),0,sizeof(long));
	loc = node.next;
	ds_read(&node, node.next, sizeof(struct ds_list_item_struct));
	do{
		printf("at%ld with val%d and next %ld\n", loc, node.item, node.next);
		loc =node.next;
		ds_read(&node, node.next, sizeof(struct ds_list_item_struct));
		i++;
	}while(loc != -1);
	printf("%d total nodes\n", i);
	
}

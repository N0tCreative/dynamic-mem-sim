/* list header file
 * Jerad Alexander Arnold
 * 1008362
 * jerad@uoguelph.ca
 * 2019-09-29
 */

struct ds_list_item_struct{
	int item;
	long next;
};

int ds_create_list();
int ds_init_list();
int ds_replace(int value, long index);
int ds_insert(int value, long index);
int ds_delete(long index);
int ds_swap(long index1, long index2);
long ds_find(int target);
int ds_read_elements(char *filename);
int ds_finish_list();
void print_list();

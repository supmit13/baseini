/*
Compile Command: gcc libini.c -o libini
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liteini.h"


int _is_empty_string(char *str){
    int slen = strlen(str);
    int isempty = 0; /* 0 means it is not empty */
    int i;
    for(i=0; i < slen; i++){
        if(str[i] != ' ' && str[i] != '\0' && str[i] != '\n'){
	    return(isempty);
        }
    }
    return(1); /* This is an empty string */
}


void get_sections(char *filepath, int **sect_count, section **sections_list){
    FILE *fp;
	char *line;
	int sect_ctr;
	
	fp = fopen(filepath, "r");
    if (fp == NULL){
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
    }
	line = (char *)malloc(LINE_LEN*sizeof(char));
	sect_ctr = 0;
	int kcntr = 0;
	int vcntr = 0;
	char *section_name;
	**sect_count = 0;
	while(fgets(line, LINE_LEN, fp) != NULL){
		if(line[0] == ';'){ /* Comment line */
		    continue;
		}
		char *key, *value;
		key = (char *)malloc((LINE_LEN/2 -1) * sizeof(char));
		value = (char *)malloc((LINE_LEN/2 -1) * sizeof(char));
        	if(line[0] == '[' && line[strlen(line) - 2] == ']'){ /* This is a fucking section. */
			
			int line_len = strlen(line);
			section_name = (char *)malloc((line_len-1)*sizeof(char));
			int i;
			for (i=1;i < line_len - 2;i++){
			    section_name[i-1] = line[i];
			}
		    	section_name[i] = '\0';
			sections_list[sect_ctr] = (section *)malloc(sizeof(section));
			sections_list[sect_ctr]->sect_name = (char *)malloc(LINE_LEN*sizeof(char));
			strcpy(sections_list[sect_ctr]->sect_name, section_name);
			
			kcntr = 0;
			vcntr = 0;
			line = (char *)malloc(LINE_LEN*sizeof(char));
			printf("\n============\nSECT_COUNT HERE = %d\n\n", **sect_count);
			**sect_count = sect_ctr;
			sections_list[sect_ctr]->sect = (section_content *)malloc(MAX_ELEMENTS_PER_SECTION * sizeof(section_content));
			sect_ctr++;
		}
		else{
			int j = 0;
			int keyctr, valctr;
			key = (char *)malloc((LINE_LEN/2 -1) * sizeof(char));
		    value = (char *)malloc((LINE_LEN/2 -1) * sizeof(char));
			int equal_flag = 0;
			keyctr = 0;
		    	valctr = 0;
			for(j=0;j < strlen(line); j++){
				if(line[j] == ' '){
					continue;
				}
				if(line[j] == '\0' || line[j] == '\n' || line[j] == ';'){
					value[valctr] = '\0';
					break;
				}
				if(line[j] == '='){
					key[keyctr] = '\0';
					equal_flag = 1;
					continue;
				}
				if(!equal_flag){
					key[keyctr] = line[j];
					keyctr++;
				}
				if(equal_flag){
					value[valctr] = line[j];
					valctr++;
				}
			}
			value[valctr] = '\0';
		}

       		/*
	    	*(sections_list[sect_ctr].sect->keys + kcntr) = (char *)malloc((LINE_LEN/2 -1) * sizeof(char));
		*(sections_list[sect_ctr].sect->values + vcntr) = (char *)malloc((LINE_LEN/2 -1) * sizeof(char));
		*/
		
		sections_list[sect_ctr-1]->sect->keys[kcntr] = (char *)malloc((LINE_LEN/2) * sizeof(char));
		sections_list[sect_ctr-1]->sect->values[vcntr] = (char *)malloc((LINE_LEN/2) * sizeof(char));

		strcpy((sections_list[sect_ctr-1]->sect)->keys[kcntr], key);
		strcpy((sections_list[sect_ctr-1]->sect)->values[vcntr], value);
		(sections_list[sect_ctr-1]->sect)->section_name = (char *)malloc(MAX_SECTION_NAME_LEN*sizeof(char));
		strcpy(sections_list[sect_ctr-1]->sect->section_name, section_name);
		
		if(_is_empty_string((sections_list[sect_ctr-1]->sect)->keys[kcntr]) && _is_empty_string((sections_list[sect_ctr-1]->sect)->values[vcntr])){
		    continue;
		}
		
		//printf("SECTION LIST NAME: %s\n", sections_list[sect_ctr-1]->sect->section_name);
		//printf("KEY= %s\n", (sections_list[sect_ctr-1]->sect)->keys[kcntr]);
		//printf("VALUE= %s\n", (sections_list[sect_ctr-1]->sect)->values[vcntr]);
		//printf("\n\n----------------------------------------------------------------------\n");
						
        	kcntr++;
		vcntr++;
		line = (char *)malloc(LINE_LEN*sizeof(char));
	}
	if(*sections_list){
	    printf("sections_list is NOT NULL.\n");
	}
	else{
	    printf("sections_list is NULL hmmmmm.\n\n");
	}
	
}

/*
Given a section name, get all elements (keys and values) as a 2D array.
The given section name should be case-sensitive. The first param is the
sections_list returned by a call to "get_sections" function. The third
param is the count of the number of sections in the ini file. The fourth
param is a pointer to the number of params in the section found. All params
are required. None is optional.
*/
void getElementsBySectionName(section **sections_list, char *section_name, int *sect_count, int *params_count){
    int sect_ctr = 0;
    char *sect_name;
    int param_ctr = 0;
    
    int kcntr = 0;
    int vcntr = 0;
    for (sect_ctr=0; sect_ctr <= *sect_count; sect_ctr++){
	printf("HERE %d\n",*sect_count);
	if(sections_list){
	    printf("Section Name: %s\n\n", sections_list[sect_ctr]->sect->section_name);
	}
	else{
	    printf("SECtion name could not be found.\n");
	}
	sect_name = (char *)malloc((strlen(sections_list[sect_ctr]->sect->section_name) + 1)*sizeof(char));
	printf("SECT CTR VALUE IS %d\n", sect_ctr);
        strcpy(sect_name, sections_list[sect_ctr]->sect->section_name);
	//printf("THERE sect_name = %s\n",sect_name);
	//printf("THERE section_name = %s\n",section_name);
        if(!strcmp(sect_name, section_name)){
	    printf("COMPARED TRUE\n");
	    //key_value_dict[param_ctr] = (char **)malloc(2 * sizeof(char *));
	    while(sections_list[sect_ctr]->sect->keys[kcntr]){
		printf("Key Name: %s\n", sections_list[sect_ctr]->sect->keys[kcntr]);
		//printf("Param Ctr: %d\n", param_ctr);
		//printf("Value 1 Name: %s\n\n", sections_list[sect_ctr]->sect->values[vcntr]);
	    	key_value_dict[param_ctr][0] = (char *)malloc(25 * sizeof(char)); /* Assuming the max length of a key is 25 characters */
		//printf("Value 2 Name: %s\n\n", sections_list[sect_ctr]->sect->values[vcntr]);
	    	key_value_dict[param_ctr][1] = (char *)malloc(40 * sizeof(char)); /* Assuming the max length of a value is 40 characters */
		printf("Value 3 Name: %s\n\n", sections_list[sect_ctr]->sect->values[vcntr]);
	    	strcpy(key_value_dict[param_ctr][0], sections_list[sect_ctr]->sect->keys[kcntr]);
		strcpy(key_value_dict[param_ctr][1], sections_list[sect_ctr]->sect->values[vcntr]);
		kcntr++;
		vcntr++;
		param_ctr++;
		*params_count = param_ctr;
            }
	    printf("RETURNING KEY VALUE DICT\n\n");
	    //return(key_value_dict);
	}
	else{
	    printf("COMPARED FALSE.\n\n");
	}
    }
    //return(NULL);
}

/*
This function returns the specific value of a given key in a given section.
The first argument is, as usual, "sections_list", which is a list of instances
of the section structure. The second and the third arguments are section
name and key name, both case-insensitive.

char *getValueByKeyFromSection(section *sections_list, char *section_name, char *keyname){
}
*/

/* This code should actually be written by the user. I wrote it here just to test the library */
int main(){
	char *file;
	//section *s;
	int *sect_count;
	//char ***key_value_dict;
	section *sections_list;
	int pcount = 0;
	
	sect_count = (int *)malloc(sizeof(int));
	*sect_count = 0;
	//printf("Address of sect_count: %d", sect_count);
	fflush(stdout);
	file = (char *)malloc(80*sizeof(char));
	strcpy(file,"./examples/test.ini");
	sections_list = (section *)malloc(MAX_SECTIONS * sizeof(section));
	get_sections(file, &sect_count, &sections_list);
	printf("\n=================\nValue of sect_count: %d\n===================\n", *sect_count);
	printf("FOUND sections_list\n\n");
	fflush(stdout);
	
	//key_value_dict = getElementsBySectionName(&sections_list, "elem-3", sect_count, &pcount);
	getElementsBySectionName(&sections_list, "elem-3", sect_count, &pcount);
	printf("Number of elements in the section is %d\n\n",pcount);
	int pctr = 0;
	
	for(pctr=0; pctr < pcount; pctr++){
	    char *key, *value;
	    key = (char *)malloc(25 * sizeof(char));
	    value = (char *)malloc(40 * sizeof(char));
	    printf("PCTR = %d\n", pctr);
	    strcpy(key, key_value_dict[pctr][0]);
	    strcpy(value, key_value_dict[pctr][1]);
	    printf("Key Value in element no. %d: %s, %s\n\n", pctr, key_value_dict[pctr][0], key_value_dict[pctr][1]);
	}
	
}


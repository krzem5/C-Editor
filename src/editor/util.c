#include <editor.h>
#include <_editor_internal.h>
#include <stdint.h>



uint32_t _copy_str(char* d,const char* s){
	uint32_t o=0;
	while (*(s+o)){
		*(d+o)=*(s+o);
		o++;
	}
	return o;
}

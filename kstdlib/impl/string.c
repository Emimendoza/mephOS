#include <string.h>

size_t strlen(const char *str){
	size_t len = 0;
	while(str[len]){
		len++;
	}
	return len;
}
int memcmp(const void *s1, const void *s2, size_t n){
	const unsigned char *p1 = s1, *p2 = s2;
	while(n--){
		if(*p1 != *p2){
			return *p1 - *p2;
		}
		p1++;
		p2++;
	}
	return 0;
}

void* memmove(void *dest, const void *src, size_t n){
	unsigned char *d = dest;
	const unsigned char *s = src;
	if(s < d && s + n > d){
		s += n;
		d += n;
		while(n--){
			*--d = *--s;
		}
		return dest;
	}
	while(n--){
		*d++ = *s++;
	}
	return dest;
}

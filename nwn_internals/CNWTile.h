#ifndef _H_CNWTILE_H_
#define _H_CNWTILE_H_

struct CNWTile_s {
	void *data;
	
	void GetLocation(int *a2, int *a3);

	void SetAnimLoop(unsigned char *a1, unsigned char *a2, unsigned char *a3);

	void GetAnimLoop(unsigned char *a1, unsigned char *a2, unsigned char *a3);

	void SetReplaceTexture(unsigned char a1);


};

#endif
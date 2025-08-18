#ifndef CONNECT_FOUR_CHIP_H	
#define CONNECT_FOUR_CHIP_H

#include "Colors.h"

class Connect_Four_Chip {
	
private:
	Color color;
	int across; 
	int down;
	int diagL;
	int diagR;

public:
	
	Connect_Four_Chip(Color color);
	Connect_Four_Chip(const Connect_Four_Chip&) = delete;
	Connect_Four_Chip& operator= (const Connect_Four_Chip&) = delete;

	void set_across(const int across);
	void set_down(const int down);
	void set_diagL(const int diagL);
	void set_diagR(const int diagR);

	int get_across() const;
	int get_down() const;
	int get_diagL() const;
	int set_diagR() const;

};

#endif
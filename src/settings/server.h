#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cctype>

class server {
public:
	server();
	virtual ~server();
	
	////////////////// getters //////////////////
	std::string get_name() { return m_name; }
	std::vector<int8_t> get_ip();
	
	////////////////// checkers //////////////////
	bool has_name();
	bool has_ip();
	bool is_valid_ip_addr();
	bool is_valid_ip_oct(int8_t ip_oct);
	
	////////////////// setters //////////////////
	bool set_ip_oct(uint8_t pos, int8_t ip_oct);

private:
	std::string m_name;
	int8_t m_ip_addr [4];
};

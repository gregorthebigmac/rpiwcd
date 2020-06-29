#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

class load_settings {
public:
	load_settings();
	virtual ~load_settings();
	
	// getters
	std::vector<std::string> get_server() { return m_server; }
	std::vector<std::string> get_ip() { return m_ip_addr; }
	
	void load_config_file();
	void parse_config_file();
	void parse_config_file2();
	int find_first_whitespace_char(std::string str);
	
	// checkers
	bool is_ip_addr(std::string str);
	
	// debug stuff
	void toggle_debug_mode() { _debug_mode = !_debug_mode; }

private:
	std::vector<std::string> m_file_lines;
	std::vector<std::string> m_interfaces;
	std::vector<std::string> m_server;
	std::vector<std::string> m_ip_addr;
	
	// debug stuff
	bool _debug_mode;
	void dump_str_vec(std::vector<std::string> vec, std::string vector_name);
	void dump_all();
};
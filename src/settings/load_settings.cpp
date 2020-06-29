#include "load_settings.h"

load_settings::load_settings() {
	_debug_mode = false;
}

load_settings::~load_settings() {}

void load_settings::load_config_file() {
	std::ifstream fin;
	if (_debug_mode) { std::cout << "Opening settings.cfg... "; }
	fin.open("config/settings.cfg");
	if (fin.is_open()) {
		if (_debug_mode) { std::cout << "[OK]" << std::endl; }
		while(!fin.eof()) {
			std::string temp;
			getline(fin, temp);
			m_file_lines.push_back(temp);
			if (_debug_mode) { std::cout << "temp = [" << temp << "]" << std::endl; }
		}
		if (_debug_mode) { dump_str_vec(m_file_lines, "m_file_lines"); }
		fin.close();
		// purging blank lines and fully commented lines
		if (_debug_mode) { std::cout << "Entering line purge..." << std::endl; }
		for (int i = 0; i < m_file_lines.size(); i++) {
			std::string temp = m_file_lines[i];
			if (_debug_mode) { std::cout << "temp = " << temp << std::endl; }
			if ((temp[0] == NULL) || (temp[0] == '#')) {
				if (_debug_mode) { std::cout << "Found a line to purge at [" << i << "]. Purging..." << std::endl; }
				m_file_lines.erase(m_file_lines.begin()+i);
				// because we just shrank the size of the vector, we need to subtract one from the index, otherwise we'll skip lines.
				i--;
			}
			else std::cout << "Line [" << i << "] should not be purged. Moving on..." << std::endl;
		}
	}
	else std::cout << "ERROR: config/settings.cfg failed to open!" << std::endl;
	parse_config_file();
}

void load_settings::parse_config_file() {
	bool content_and_comment_found = false;
	if (_debug_mode) { std::cout << "Entering parse_config_file..." << std::endl; }
	std::vector<std::string> temp_entry;
	for (int i = 0; i < m_file_lines.size(); i++) {
		std::string temp_line = m_file_lines[i];
		if (_debug_mode) { std::cout << "temp_line = [" << temp_line << "]" << std::endl; }
		int found = find_first_whitespace_char(temp_line);
		if (found != -1) {
			std::string temp_word = temp_line.substr(0, found);
			if (temp_word == "iface") {
				temp_entry.push_back(temp_word);
				temp_line.erase(0, found);
				if (_debug_mode) { std::cout << "found interface! " << temp_word << std::endl; }
			}
			else if (temp_word == "server") {
				temp_entry.push_back(temp_word);
				temp_line.erase(0, found);
				if (_debug_mode) { std::cout << "found server! " << temp_word << std::endl; }
			}
			else {
				std::cout << "ERROR: Garbage info in line " << i << " of settings.cfg" << std::endl;
				std::cout << "bad entry: " << temp_word << std::endl;
				continue;
			}
		}
		if (_debug_mode) { std::cout << "Entering while erase white space... " << std::endl; }
		while (isspace(temp_line[0])) {
			std::cout << "Found whitespace character! Purging..." << std::endl;
			temp_line.erase(0, 1);
			std::cout << "temp_line = " << temp_line << std::endl;
		}
		found = find_first_whitespace_char(temp_line);
		if (found != -1) {
			std::string temp_word = temp_line.substr(0, found);
			if (temp_entry[0] == "iface") {
				temp_entry.push_back(temp_word);
				temp_line.erase(0, found);
			}
			else if (temp_entry[0] == "server") {
				temp_entry.push_back(temp_word);
				temp_line.erase(0, found);
			}
			else std::cout << "Garbage data. Moving on..." << std::endl;
		}
		if (_debug_mode) { std::cout << "Entering while erase white space..." << std::endl; }
		while (isspace(temp_line[0])) {
			std::cout << "Found whitespace character! Purging..." << std::endl;
			temp_line.erase(0, 1);
			std::cout << "temp_line = " << temp_line << std::endl;
		}
		temp_entry.push_back(temp_line);
		if (temp_entry[0] == "iface") {
			if (_debug_mode) { std::cout << "adding " << temp_entry[1] << " to interfaces" << std::endl; }
			m_interfaces.push_back(temp_entry[1]);
			if (temp_line.size() > 4) {	// For some reason, if the rest of the line is blank, the size of temp_line is 4.
				if (_debug_mode) { std::cout << "adding " << temp_entry[2] << " to mac addresses" << std::endl; }
				//m_mac_addr.push_back(temp_entry[2]);
			}
			else {
				if (_debug_mode) {
					std::cout << "temp_line.size() = " << temp_line.size() << std::endl;
					std::cout << "temp_line = " << temp_line << std::endl;
				}
			}
		}
		else if (temp_entry[0] == "server") {
			if (_debug_mode) { std::cout << "adding " << temp_entry[1] << " to servers" << std::endl; }
			m_server.push_back(temp_entry[1]);
			if (_debug_mode) { std::cout << "adding " << temp_entry[2] << " to ip addresses" << std::endl; }
			m_ip_addr.push_back(temp_entry[2]);
		}
		temp_entry.clear();
	}
	if (_debug_mode) { dump_all(); }
}

int load_settings::find_first_whitespace_char(std::string str) {
	for (int i = 0; i < str.size(); i++) {
		if (isspace(str[i])) {
			size_t found_it = i;
			return found_it;
		}
	}
	return -1;
}

////////////////// checkers //////////////////
bool load_settings::is_ip_addr(std::string str) {
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '.')
			return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
// 								DEBUG FUNCTIONS								  //
////////////////////////////////////////////////////////////////////////////////
void load_settings::dump_str_vec(std::vector<std::string> vec, std::string vec_name) {
	std::cout << "Dumping contents of " << vec_name << "..." << std::endl;
	for (int i = 0; i < vec.size(); i++) {
		std::cout << "[" << i << "] " << vec[i] << std::endl;
	}
}

void load_settings::dump_all() {
	dump_str_vec(m_file_lines, "m_file_lines");
	dump_str_vec(m_interfaces, "m_interfaces");
	dump_str_vec(m_server, "m_server");
	dump_str_vec(m_ip_addr, "m_ip_addr");
}

void load_settings::parse_config_file2() {
	if (_debug_mode) { std::cout << "Entering pase_config_file2..." << std::endl; }
	std::vector<std::string> temp_entry;
	for (int i = 0; i < m_file_lines.size(); i++) {
		std::string temp_line = m_file_lines[i];
		if (_debug_mode) { std::cout << "temp_line = [" << temp_line << "]" << std::endl; }
		int found_ws = find_first_whitespace_char(temp_line);
		while (found_ws != -1) {
			std::string temp_word = temp_line.substr(0, found_ws);
			if (is_ip_addr(m_file_lines[i])) {
				temp_entry.push_back(temp_word);
			}
		}
	}
}
#include "server.h"

server::server() {
	for (int i = 0; i < 4; i++)
		m_ip_addr[i] = -1;
}

server::~server() {}

////////////////// getters //////////////////
std::vector<int8_t> server::get_ip() {
	std::vector<int8_t> ip_addr;
	for (int i = 0; i < 4; i++)
		ip_addr.push_back(m_ip_addr[i]);
	if (has_ip() == false)
		std::cout << "ERROR: no IP Address found!" << std::endl;
	return ip_addr;
}

////////////////// checkers //////////////////
bool server::has_name() {
	if (m_name == "")
		return false;
	else
		return true;
}

bool server::has_ip() {
	for (int i = 0; i < 4; i++) {
		if (m_ip_addr[i] == -1)
			return false;
	}
	return true;
}

bool server::is_valid_ip_addr() {
	for (int i = 0; i < 4; i++) {
		if (is_valid_ip_oct(m_ip_addr[i]))
			continue;
		else
			return false;
	}
	return true;
}

bool server::is_valid_ip_oct(int8_t ip_oct) {
	if ((ip_oct < 0) || (ip_oct > 255))
		return false;
	else
		return true;
}

////////////////// setters //////////////////
bool server::set_ip_oct(uint8_t pos, int8_t ip_oct) {
	if (is_valid_ip_oct(ip_oct)) {
		m_ip_addr[pos] = ip_oct;
		return true;
	}
	else {
		std::cout << "ERROR: IP address invalid!" << std::endl;
		std::cout << ip_oct << " is not a valid IP address octet!" << std::endl;
		return false;
	}
}
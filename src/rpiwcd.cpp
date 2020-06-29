#include "command/command.hpp"
#include "settings/load_settings.h"

using std::cout;
using std::cin;
using std::string;

command cmd;
load_settings settings;

int main() {
	settings.toggle_debug_mode();
	settings.load_config_file();
	return 0;
}
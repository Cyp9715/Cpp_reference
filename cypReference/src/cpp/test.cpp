﻿#include "cyp_file.hpp"

int main()
{
	cyp::file::FileCommunication f;
	f.sendFile("192.168.200.134", 9998, "C:\\Users\\Cyphe\\Desktop\\TXT.txt");
}
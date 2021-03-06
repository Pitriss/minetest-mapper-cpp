/*
 * =====================================================================
 *        Version:  1.0
 *        Created:  22.08.2012 15:15:54
 *         Author:  Miroslav Bendík
 *        Company:  LinuxOS.sk
 * =====================================================================
 */

#include <cstdlib>
#include <getopt.h>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include "TileGenerator.h"

using namespace std;

void usage()
{
	 const char *usage_text = "minetestmapper.py [options]\n\
  -i/--input <world_path>\n\
  -o/--output <output_image.png>\n\
  --bgcolor <color>\n\
  --scalecolor <color>\n\
  --playercolor <color>\n\
  --origincolor <color>\n\
  --drawscale\n\
  --drawplayers\n\
  --draworigin\n\
  --geometry x:y+w+h\n\
Color format: '#000000'\n";
	std::cout << usage_text;
}

int main(int argc, char *argv[])
{
	static struct option long_options[] =
	{
		{"help", no_argument, 0, 'h'},
		{"input", required_argument, 0, 'i'},
		{"output", required_argument, 0, 'o'},
		{"bgcolor", required_argument, 0, 'b'},
		{"scalecolor", required_argument, 0, 's'},
		{"origincolor", required_argument, 0, 'r'},
		{"playercolor", required_argument, 0, 'p'},
		{"draworigin", no_argument, 0, 'R'},
		{"drawplayers", no_argument, 0, 'P'},
		{"drawscale", no_argument, 0, 'S'},
		{"geometry", required_argument, 0, 'g'},
	};

	string input;
	string output;

	TileGenerator generator;
	generator.parseColorsFile("colors.txt");
	int option_index = 0;
	int c = 0;
	while (1) {
		c = getopt_long(argc, argv, "hi:o:", long_options, &option_index);
		if (c == -1) {
			if (input.empty() || output.empty()) {
				usage();
				exit(-1);
			}
			break;
		}
		switch (c) {
			case 'h':
				usage();
				exit(0);
				break;
			case 'i':
				input = optarg;
				break;
			case 'o':
				output = optarg;
				break;
			case 'b':
				generator.setBgColor(optarg);
				break;
			case 's':
				generator.setScaleColor(optarg);
				break;
			case 'r':
				generator.setOriginColor(optarg);
				break;
			case 'p':
				generator.setPlayerColor(optarg);
				break;
			case 'R':
				generator.setDrawOrigin(true);
				break;
			case 'P':
				generator.setDrawPlayers(true);
				break;
			case 'S':
				generator.setDrawScale(true);
				break;
			case 'g': {
					istringstream geometry;
					geometry.str(optarg);
					int x, y, w, h;
					char c;
					geometry >> x >> c >> y >> w >> h;
					if (geometry.fail() || c != ':' || w < 1 || h < 1) {
						usage();
						exit(-1);
					}
					generator.setGeometry(x, y, w, h);
				}
				break;
			default:
				abort();
		}
	}
	generator.generate(input, output);
}

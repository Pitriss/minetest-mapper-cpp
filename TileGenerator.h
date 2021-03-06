/*
 * =====================================================================
 *        Version:  1.0
 *        Created:  23.08.2012 12:35:59
 *         Author:  Miroslav Bendík
 *        Company:  LinuxOS.sk
 * =====================================================================
 */

#ifndef TILEGENERATOR_H_JJNUCARH
#define TILEGENERATOR_H_JJNUCARH

#include <gd.h>
#include <iosfwd>
#include <list>
#include <map>
#include <set>
#include <sqlite3.h>
#include <stdint.h>
#include <string>
#include "PixelAttributes.h"

struct Color {
	Color(): r(255), g(255), b(255) {};
	Color(uint8_t r, uint8_t g, uint8_t b): r(r), g(g), b(b) {};
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct BlockPos {
	int x;
	int y;
	int z;
	bool operator<(const BlockPos& p) const
	{
		if (z > p.z) {
			return true;
		}
		if (z < p.z) {
			return false;
		}
		if (y > p.y) {
			return true;
		}
		if (y < p.y) {
			return false;
		}
		if (x > p.x) {
			return true;
		}
		if (x < p.x) {
			return false;
		}
		return false;
	}
};

class DbError {
};

class ColorError {
};

class VersionError {
};


class TileGenerator
{
private:
	typedef std::basic_string<unsigned char> unsigned_string;
	typedef std::map<std::string, Color> ColorMap;
	typedef std::pair<BlockPos, unsigned_string> Block;
	typedef std::list<Block> BlockList;

public:
	TileGenerator();
	~TileGenerator();
	void setBgColor(const std::string &bgColor);
	void setScaleColor(const std::string &scaleColor);
	void setOriginColor(const std::string &originColor);
	void setPlayerColor(const std::string &playerColor); Color parseColor(const std::string &color);
	void setDrawOrigin(bool drawOrigin);
	void setDrawPlayers(bool drawPlayers);
	void setDrawScale(bool drawScale);
	void setGeometry(int x, int y, int w, int h);
	void parseColorsFile(const std::string &fileName);
	void generate(const std::string &input, const std::string &output);

private:
	void parseColorsStream(std::istream &in);
	void openDb(const std::string &input);
	void loadBlocks();
	BlockPos decodeBlockPos(sqlite3_int64 blockId) const;
	void createImage();
	void renderMap();
	std::list<int> getZValueList() const;
	std::map<int, BlockList> getBlocksOnZ(int zPos, sqlite3_stmt *statement) const;
	void renderMapBlock(const unsigned_string &mapBlock, const BlockPos &pos, int version);
	void renderShading(int zPos);
	void renderScale();
	void renderOrigin();
	void renderPlayers(const std::string &inputPath);
	void writeImage(const std::string &output);
	void printUnknown();
	int getImageX(int val) const;
	int getImageY(int val) const;

private:
	Color m_bgColor;
	Color m_scaleColor;
	Color m_originColor;
	Color m_playerColor;
	bool m_drawOrigin;
	bool m_drawPlayers;
	bool m_drawScale;
	int m_border;

	sqlite3 *m_db;
	gdImagePtr m_image;
	PixelAttributes m_blockPixelAttributes;
	int m_xMin;
	int m_xMax;
	int m_zMin;
	int m_zMax;
	int m_geomX;
	int m_geomY;
	int m_geomX2;
	int m_geomY2;
	int m_mapWidth;
	int m_mapHeight;
	std::list<std::pair<int, int> > m_positions;
	std::map<int, std::string> m_nameMap;
	ColorMap m_colors;
	uint16_t m_readedPixels[16];
	std::set<std::string> m_unknownNodes;

	int m_blockAirId;
	int m_blockIgnoreId;
}; /* -----  end of class TileGenerator  ----- */

#endif /* end of include guard: TILEGENERATOR_H_JJNUCARH */


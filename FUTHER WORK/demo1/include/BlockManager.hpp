
#include <map>
#include <set>
#include <string>

#include "Block.hpp"


class BlockManager
{
public:
	enum BlockSide
	{
		Top = 1 << 0,
		Down = 1 << 1,
		Forward = 1 << 2,
		Backward = 1 << 3,
		Left = 1 << 4,
		Right = 1 << 5,
	};
	static unsigned int getBlockTexture(std::string type, BlockSide side);
	static void registerBlockType(std::string type);
	static void setBlockTypeTexture(BlockSide sides, unsigned int texture);
private:
	static std::set<std::string> registered_block_types;
	static unsigned int unknown_block_texture;
	static std::map<std::string, unsigned int>   LEFT_SIDE_TEXTURES;
	static std::map<std::string, unsigned int>  RIGHT_SIDE_TEXTURES;
	static std::map<std::string, unsigned int>  FRONT_SIDE_TEXTURES;
	static std::map<std::string, unsigned int>   BACK_SIDE_TEXTURES;
	static std::map<std::string, unsigned int> BOTTOM_SIDE_TEXTURES;
	static std::map<std::string, unsigned int>    TOP_SIDE_TEXTURES;
};
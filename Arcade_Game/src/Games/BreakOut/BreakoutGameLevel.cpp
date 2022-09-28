#include "BreakoutGameLevel.h"
#include "Ball.h"
#include "App.h"
#include "FileCommandLoader.h"



BreakoutGameLevel::BreakoutGameLevel()
{
}

void BreakoutGameLevel::Init(const AARectangle& boundary)
{
	CreateDefaultLevel(boundary);
}

void BreakoutGameLevel::Load(const std::vector<Block>& blocks)
{
	mBlocks.clear();
	mBlocks = blocks; //maybe use move semantics?
}

void BreakoutGameLevel::Update(uint32_t deltaTime, Ball& ball)
{
	std::vector<Block> collidedBlocks;

	BoundaryEdge edgeToBounceOffOf;
	Block* noptrBlockToBounceOffOf = nullptr;

	float largestMag = -1.0f;
	for(auto& block : mBlocks)
	{
		BoundaryEdge edge;
		Vec2D offsetCollision;
		if (!block.IsDestroyed() && block.HasCollided(ball.GetBoundaryBox(), edge, offsetCollision))
		{
			collidedBlocks.push_back(block);
			float mag = offsetCollision.Mag();
			if (mag > largestMag)
			{
				edgeToBounceOffOf = edge;
				noptrBlockToBounceOffOf = &block;
				largestMag = mag;
			}
		}
	}
	if (noptrBlockToBounceOffOf)
	{
		noptrBlockToBounceOffOf->Bounce(ball, edgeToBounceOffOf);
		noptrBlockToBounceOffOf->ReduceHP();
	}

	//if for some reason we are still colliding we flush again
	for (const auto& block : collidedBlocks)
	{
		BoundaryEdge edge;
		Vec2D offsetCollision;
		if (block.HasCollided(ball.GetBoundaryBox(), edge, offsetCollision))
		{
			ball.MakeFlushWithEdge(edge, offsetCollision, true);
		}
	}
}

void BreakoutGameLevel::Draw(Screen& screen)
{
	for (auto& block : mBlocks)
	{
		if (!block.IsDestroyed())
		{
			block.Draw(screen);
		}
	}
}

std::vector<BreakoutGameLevel> BreakoutGameLevel::LoadLevelsFromFile(const std::string& filePath)
{
	std::vector<BreakoutGameLevel> levels;

	std::vector<LayoutBlock> layoutBlocks;

	std::vector<Block> levelBlocks;

	int width = 0;
	int height = 0;

	FileCommandLoader fileLoader;

	Command levelComand;

	levelComand.command = "level";
	levelComand.parseFunc = [&](ParseFuncParams params) {
		if (levels.size() > 0)
		{
			//load first level we have none
			levels.back().Load(levelBlocks);

		}//else clear the load level to start fresh
	
		layoutBlocks.clear();
		levelBlocks.clear();
		width = 0;
		height = 0;
		
		//create new level
		BreakoutGameLevel level;

		AARectangle levelBoundary(Vec2D::Zero, SCREEN_WIDTH, SCREEN_HEIGHT);
		level.Init(levelBoundary);

		levels.push_back(level);

	};

	fileLoader.AddCommand(levelComand);

	Command blockCommand;
	blockCommand.command = "block";
	blockCommand.parseFunc = [&](ParseFuncParams params) {

		LayoutBlock lb;
		layoutBlocks.push_back(lb);

		
	};

	fileLoader.AddCommand(blockCommand);

	Command symbolCommand;
	symbolCommand.command = "symbol";
	symbolCommand.parseFunc = [&] (ParseFuncParams params) {

		layoutBlocks.back().symbol = FileCommandLoader::ReadChar(params);
	};

	fileLoader.AddCommand(symbolCommand);

	 Command fillColorCommand;
	 fillColorCommand.command = "fillcolor";
	 fillColorCommand.parseFunc = [&](ParseFuncParams params) {


		layoutBlocks.back().color = FileCommandLoader::ReadColor(params);

	 };

	 fileLoader.AddCommand(fillColorCommand);

	 Command hpCommand;
	 hpCommand.command = "hp";
	 hpCommand.parseFunc = [&](ParseFuncParams params) {

		layoutBlocks.back().hp = FileCommandLoader::ReadInt(params);
	
	 };

	 fileLoader.AddCommand(hpCommand);

	Command widthCommand;
	widthCommand.command = "width";
	widthCommand.parseFunc = [&](ParseFuncParams params) {

		width = FileCommandLoader::ReadInt(params);
		
	};

	fileLoader.AddCommand(widthCommand);

	Command heightCommand;
	heightCommand.command = "height";
	heightCommand.parseFunc = [&](ParseFuncParams params) {

		height = FileCommandLoader::ReadInt(params);
	};

	fileLoader.AddCommand(heightCommand);

	Command layoutCommand;
	layoutCommand.commandType = COMMAND_MULTI_LINE;
	layoutCommand.command = "layout";
	layoutCommand.parseFunc = [&](ParseFuncParams params) {

		
		float startingX = 0.f;
		AARectangle blockRect
		(
			Vec2D(startingX, (params.LineNum + 1)* BLOCK_HEIGHT),
			BLOCK_WIDTH,
			BLOCK_HEIGHT
		);

		for (size_t c = 0; c < params.line.length(); c++)
		{
	
			if (params.line[c] != '-')
			{
				LayoutBlock layoutBlock = BreakoutGameLevel::FindLayoutBlockForSymbol(layoutBlocks, params.line[c]);

				Block b;
				b.Init(blockRect, layoutBlock.hp, Color::Black(), layoutBlock.color);
				levelBlocks.push_back(b);
		
			}
			blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
		}
	};

	fileLoader.AddCommand(layoutCommand);

	fileLoader.LoadFile(filePath);

	if (levels.size() > 0)
	{
		levels.back().Load(levelBlocks);
	}

	return levels;
}

void BreakoutGameLevel::CreateDefaultLevel(const AARectangle& boundary)
{
	mBlocks.clear();

	const int NUM_BLOCKS_ACROSS = (static_cast<int>(boundary.GetWidth()) - 2 * BLOCK_WIDTH) / BLOCK_WIDTH;

	const int NUM_BLOCKS_ROWS = 5;

	float startX = (static_cast<int>(boundary.GetWidth() - NUM_BLOCKS_ACROSS * (BLOCK_WIDTH + 1))) / 2;
	Color colors[NUM_BLOCKS_ROWS];
	colors[0] = Color::Red();
	colors[1] = Color::Magenta();
	colors[2] = Color::Yellow();
	colors[3] = Color::Green();
	colors[4] = Color::Cyan();

	for (size_t r = 0; r < NUM_BLOCKS_ROWS; r++)
	{
		AARectangle blockRect
		{
			Vec2D(startX, BLOCK_HEIGHT * (r + 1)),
			BLOCK_WIDTH,
			BLOCK_HEIGHT 
		};
		for (size_t c = 0; c < NUM_BLOCKS_ACROSS; c++)
		{
			Block b;
			b.Init(blockRect, r + 1, Color::Black(), colors[r]);
			mBlocks.push_back(b);
			blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
		}

	}

}

LayoutBlock BreakoutGameLevel::FindLayoutBlockForSymbol(const std::vector<LayoutBlock>& blocks, char symbol)
{
	for (const auto& block : blocks)
	{
		if (block.symbol == symbol)
			return block;
	}

	return LayoutBlock();
}

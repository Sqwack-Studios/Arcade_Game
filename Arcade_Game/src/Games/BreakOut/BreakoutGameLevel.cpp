#include "BreakoutGameLevel.h"
#include "Ball.h"	



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

void BreakoutGameLevel::CreateDefaultLevel(const AARectangle& boundary)
{
	mBlocks.clear();

	const int BLOCK_WIDTH = 40;
	const int BLOCK_HEIGHT = 20;
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

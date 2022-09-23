#include "Excluder.h"
#include "Utils.h"
#include <math.h>
#include <cassert>

void Excluder::Init(const AARectangle& rect, bool reverseNormals)
{
    mAARect = rect;
    mReverseNormals = reverseNormals;
    SetupEdges();
}

void Excluder::SetupEdges()
{
    //TOP_EDGE
    mEdges[TOP_EDGE].edge = 
    { mAARect.GetTopLeftPoint().GetX(),
      mAARect.GetTopLeftPoint().GetY(), 
      mAARect.GetBottomRightPoint().GetX(), 
      mAARect.GetTopLeftPoint().GetY()
    };

    mEdges[TOP_EDGE].normal = Vec2D::Up;
    
    //LEFT_EDGE
    mEdges[LEFT_EDGE].edge =
    { mAARect.GetTopLeftPoint().GetX(),
      mAARect.GetTopLeftPoint().GetY(),
      mAARect.GetTopLeftPoint().GetX(),
      mAARect.GetBottomRightPoint().GetY() 
    };

    mEdges[LEFT_EDGE].normal = Vec2D::Left;

    //BOTTOM_EDGE
    mEdges[BOTTOM_EDGE].edge =
    { mAARect.GetTopLeftPoint().GetX(),
      mAARect.GetBottomRightPoint().GetY(),
      mAARect.GetBottomRightPoint().GetX(),
      mAARect.GetBottomRightPoint().GetY() 
    };

    mEdges[BOTTOM_EDGE].normal = Vec2D::Down;

    //RIGHT_EDGE
    mEdges[RIGHT_EDGE].edge =
    { mAARect.GetBottomRightPoint().GetX(),
      mAARect.GetTopLeftPoint().GetY(),
      mAARect.GetBottomRightPoint().GetX(),
      mAARect.GetBottomRightPoint().GetY() 
    };

    mEdges[RIGHT_EDGE].normal = Vec2D::Right;
    
    if (mReverseNormals)
    {
        for (auto& edge : mEdges)
        {
            edge.normal = -edge.normal;
        }
    }
}

bool Excluder::HasCollided(const AARectangle& rect, BoundaryEdge& edge, Vec2D& Outoffset) const
{
    //Calculate which side of the rectangles is overlaping the most
    if (mAARect.Intersects(rect))
    {
        float yMin = mAARect.GetTopLeftPoint().GetY() >= (rect.GetTopLeftPoint().GetY()) ?
            mAARect.GetTopLeftPoint().GetY() : rect.GetTopLeftPoint().GetY();

        float yMax  = mAARect.GetBottomRightPoint().GetY() <= (rect.GetBottomRightPoint().GetY()) ?
            mAARect.GetBottomRightPoint().GetY() : rect.GetBottomRightPoint().GetY();

        float ySize = yMax - yMin;

        float xMin = mAARect.GetTopLeftPoint().GetX() >= rect.GetTopLeftPoint().GetX() ?
            mAARect.GetTopLeftPoint().GetX() : rect.GetTopLeftPoint().GetX();

        float xMax = mAARect.GetBottomRightPoint().GetX() <= rect.GetBottomRightPoint().GetX() ?
            mAARect.GetBottomRightPoint().GetX() : rect.GetBottomRightPoint().GetX();

        float xSize = xMax - xMin;

        
        //Select a edge based on the size of the overlapping sides
        if (xSize > ySize)
        {
            if (rect.GetCenterPoint().GetY() > mAARect.GetCenterPoint().GetY())
            {
                edge = mEdges[BOTTOM_EDGE];
            }
            else
            {
                edge = mEdges[TOP_EDGE];
            }
        }
        else
        {
            if (rect.GetCenterPoint().GetX() < mAARect.GetCenterPoint().GetX())
            {
                edge = mEdges[LEFT_EDGE];
            }
            else
            {
                edge = mEdges[RIGHT_EDGE];
            }
        }

        //How much do we have to move the rectangle in order to stop overlapping?
        if (!IsEqual(edge.normal.GetY(), 0))
        {
            Outoffset = (ySize + 1) * edge.normal;
        }
        else
        {
            Outoffset = (xSize + 1) * edge.normal;
        }

        return true;
    }
    Outoffset = Vec2D::Zero;
    return false;
}


void Excluder::MoveBy(const Vec2D& delta)
{
    mAARect.MoveBy(delta);
    SetupEdges();
}

void Excluder::MoveTo(const Vec2D& point)
{
    mAARect.MoveTo(point);
    SetupEdges();
}

const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const
{
    assert(edge != NUM_EDGES);

    return mEdges[edge];
}

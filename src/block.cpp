#include "block.h"

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "world_matrices.h"

std::vector<GLfloat> GetBlockFaceVertices(BlockFaces face)
{
    std::vector<GLfloat> faceVertices = std::vector<GLfloat>();

    switch (face)
    {
        case BlockFaces::Front:
            {
                faceVertices.insert(
                        faceVertices.end(),
                        {
                                0.5f, 0.5f, 0.5f,
                                -0.5f, 0.5f, 0.5f,
                                0.5f, -0.5f, 0.5f,
                                -0.5f, -0.5f, 0.5f
                            }
                         );
            }
            break;
        case BlockFaces::Back:
        {
            faceVertices.insert(
                    faceVertices.end(),
                    {
                        0.5f, 0.5f, -0.5f,
                         -0.5f, 0.5f, -0.5f,
                         0.5f, -0.5f, -0.5f,
                         -0.5f, -0.5f, -0.5f
                    }
            );
        }
        break;
        case BlockFaces::Right:
        {
            faceVertices.insert(
                    faceVertices.end(),
                    {
                            0.5f, 0.5f, 0.5f, // Top-Front-Right
                            0.5f, 0.5f, -0.5f,  // Top-Back-Right
                            0.5f, -0.5f, 0.5f, // Bottom-Front-Right
                            0.5f, -0.5f, -0.5f // Bottom-Back-Right
                    }
            );
        }
        break;
        case BlockFaces::Left:
        {
            faceVertices.insert(
                    faceVertices.end(),
                    {
                            -0.5f, 0.5f, 0.5f, // Top-Front-Left
                            -0.5f, 0.5f, -0.5f, // Top-Back-Left
                            -0.5f, -0.5f, 0.5f, // Bottom-Front-Left
                            -0.5f, -0.5f, -0.5f, // Bottom-Back-Left
                    }
            );
        }
        break;
        case BlockFaces::Top:
        {
            faceVertices.insert(
                    faceVertices.end(),
                    {
                            0.5f, 0.5f, 0.5f, // Top-Front-Right
                            -0.5f, 0.5f, 0.5f, // Top-Front-Left
                            0.5f, 0.5f, -0.5f, // Top-Back-Right
                            -0.5f, 0.5f, -0.5f, // Top-Back-Left
                    }
            );
        }
        break;
        case BlockFaces::Bottom:
        {
            faceVertices.insert(
                    faceVertices.end(),
                    {
                            0.5f, -0.5f, 0.5f, // Bottom-Front-Right
                            -0.5f, -0.5f, 0.5f, // Bottom-Front-Left
                            0.5f, -0.5f, -0.5f, // Bottom-Back-Right
                            -0.5f, -0.5f, -0.5f, // Bottom-Back-Left
                    }
            );
        }
        break;
    }

    return faceVertices;
}

std::vector<GLint> GetBlockFaceIndices(BlockFaces face, int offset)
{
    std::vector<GLint> faceIndices = std::vector<GLint>();

    switch(face)
    {
        case BlockFaces::Front:
        {
            faceIndices.insert(
                    faceIndices.end(),
                    {
                            3 + offset, 0 + offset, 2 + offset, 0 + offset, 3 + offset, 1 + offset
                    }
            );
        }
        break;
        case BlockFaces::Back:
        {
            faceIndices.insert(
                    faceIndices.end(),
                    {
                            7 + offset, 6 + offset, 4 + offset, 4 + offset, 5 + offset, 7 + offset
                    }
            );
        }
        break;
        case BlockFaces::Right:
        {
            faceIndices.insert(
                    faceIndices.end(),
                    {
                            8 + offset, 9 + offset, 11 + offset, 11 + offset, 10 + offset, 8 + offset
                    }
            );
        }
        break;
        case BlockFaces::Left:
        {
            faceIndices.insert(
                    faceIndices.end(),
                    {
                            12 + offset, 15 + offset, 13 + offset, 15 + offset, 12 + offset, 14 + offset
                    }
            );
        }
        break;
        case BlockFaces::Top:
        {
            faceIndices.insert(
                    faceIndices.end(),
                    {
                            19 + offset, 16 + offset, 17 + offset, 18 + offset, 16 + offset, 19 + offset
                    }
            );
        }
        break;
        case BlockFaces::Bottom:
        {
            faceIndices.insert(
                    faceIndices.end(),
                    {
                            23 + offset, 20 + offset, 22 + offset, 20 + offset, 23 + offset, 21 + offset
                    }
            );
        }
        break;
    }

    return faceIndices;
}

std::vector<GLfloat> GetBlockTextureCoordinates(BlockFaces face, BlockType type, TextureAtlas &textureAtlas)
{
    std::vector<GLfloat> textureCoordinates = std::vector<GLfloat>();
    BlockTexture blockTexture = textureAtlas.getBlockTexture(type);

    switch(face)
    {
        case BlockFaces::Front:
        {
            textureCoordinates.push_back(blockTexture.faces.front.position.x + blockTexture.faces.front.size.x);
            textureCoordinates.push_back(blockTexture.faces.front.position.y + blockTexture.faces.front.size.y);

            textureCoordinates.push_back(blockTexture.faces.front.position.x);
            textureCoordinates.push_back(blockTexture.faces.front.position.y + blockTexture.faces.front.size.y);

            textureCoordinates.push_back(blockTexture.faces.front.position.x + blockTexture.faces.front.size.x);
            textureCoordinates.push_back(blockTexture.faces.front.position.y);

            textureCoordinates.push_back(blockTexture.faces.front.position.x);
            textureCoordinates.push_back(blockTexture.faces.front.position.y);
        }
        break;
        case BlockFaces::Back:
        {
            textureCoordinates.push_back(blockTexture.faces.back.position.x + blockTexture.faces.back.size.x);
            textureCoordinates.push_back(blockTexture.faces.back.position.y + blockTexture.faces.back.size.y);

            textureCoordinates.push_back(blockTexture.faces.back.position.x);
            textureCoordinates.push_back(blockTexture.faces.back.position.y + blockTexture.faces.back.size.y);

            textureCoordinates.push_back(blockTexture.faces.back.position.x + blockTexture.faces.back.size.x);
            textureCoordinates.push_back(blockTexture.faces.back.position.y);

            textureCoordinates.push_back(blockTexture.faces.back.position.x);
            textureCoordinates.push_back(blockTexture.faces.back.position.y);
        }
        break;
        case BlockFaces::Right:
        {
            textureCoordinates.push_back(blockTexture.faces.right.position.x + blockTexture.faces.right.size.x);
            textureCoordinates.push_back(blockTexture.faces.right.position.y + blockTexture.faces.right.size.y);

            textureCoordinates.push_back(blockTexture.faces.right.position.x);
            textureCoordinates.push_back(blockTexture.faces.right.position.y + blockTexture.faces.right.size.y);

            textureCoordinates.push_back(blockTexture.faces.right.position.x + blockTexture.faces.right.size.x);
            textureCoordinates.push_back(blockTexture.faces.right.position.y);

            textureCoordinates.push_back(blockTexture.faces.right.position.x);
            textureCoordinates.push_back(blockTexture.faces.right.position.y);
        }
        break;
        case BlockFaces::Left:
        {
            textureCoordinates.push_back(blockTexture.faces.left.position.x + blockTexture.faces.left.size.x);
            textureCoordinates.push_back(blockTexture.faces.left.position.y + blockTexture.faces.left.size.y);

            textureCoordinates.push_back(blockTexture.faces.left.position.x);
            textureCoordinates.push_back(blockTexture.faces.left.position.y + blockTexture.faces.left.size.y);

            textureCoordinates.push_back(blockTexture.faces.left.position.x + blockTexture.faces.left.size.x);
            textureCoordinates.push_back(blockTexture.faces.left.position.y);

            textureCoordinates.push_back(blockTexture.faces.left.position.x);
            textureCoordinates.push_back(blockTexture.faces.left.position.y);
        }
        break;
        case BlockFaces::Top:
        {
            textureCoordinates.push_back(blockTexture.faces.top.position.x + blockTexture.faces.top.size.x);
            textureCoordinates.push_back(blockTexture.faces.top.position.y + blockTexture.faces.top.size.y);

            textureCoordinates.push_back(blockTexture.faces.top.position.x);
            textureCoordinates.push_back(blockTexture.faces.top.position.y + blockTexture.faces.top.size.y);

            textureCoordinates.push_back(blockTexture.faces.top.position.x + blockTexture.faces.top.size.x);
            textureCoordinates.push_back(blockTexture.faces.top.position.y);

            textureCoordinates.push_back(blockTexture.faces.top.position.x);
            textureCoordinates.push_back(blockTexture.faces.top.position.y);
        }
        break;
        case BlockFaces::Bottom:
        {
            textureCoordinates.push_back(blockTexture.faces.bottom.position.x + blockTexture.faces.bottom.size.x);
            textureCoordinates.push_back(blockTexture.faces.bottom.position.y + blockTexture.faces.bottom.size.y);

            textureCoordinates.push_back(blockTexture.faces.bottom.position.x);
            textureCoordinates.push_back(blockTexture.faces.bottom.position.y + blockTexture.faces.bottom.size.y);

            textureCoordinates.push_back(blockTexture.faces.bottom.position.x + blockTexture.faces.bottom.size.x);
            textureCoordinates.push_back(blockTexture.faces.bottom.position.y);

            textureCoordinates.push_back(blockTexture.faces.bottom.position.x);
            textureCoordinates.push_back(blockTexture.faces.bottom.position.y);
        }
        break;
    }

    return textureCoordinates;
}

void FindVisibleFacesInBlocks(std::vector<Block>& blocks)
{
    for (auto& block : blocks)
    {
        int numAdjacentBlocks = 0;

        block.visibleFaces.clear();

        for (const auto& blockCheck : blocks)
        {
            if (block.pos != blockCheck.pos) {
                int xDiff = block.pos.x - blockCheck.pos.x;
                int yDiff = block.pos.y - blockCheck.pos.y;
                int zDiff = block.pos.z - blockCheck.pos.z;

                if (xDiff == -1 && blockCheck.pos.y == block.pos.y && blockCheck.pos.z == block.pos.z)
                {
                    block.visibleFaces.push_back(BlockFaces::Left);
                }
                else if (xDiff == 1 && blockCheck.pos.y == block.pos.y && blockCheck.pos.z == block.pos.z)
                {
                    block.visibleFaces.push_back(BlockFaces::Right);
                }
                else if (yDiff == -1 && blockCheck.pos.x == block.pos.x && blockCheck.pos.z == block.pos.z)
                {
                    block.visibleFaces.push_back(BlockFaces::Bottom);
                }
                else if (yDiff == 1 && blockCheck.pos.x == block.pos.x && blockCheck.pos.z == block.pos.z)
                {
                    block.visibleFaces.push_back(BlockFaces::Top);
                }
                else if (zDiff == -1 && blockCheck.pos.x == block.pos.x && blockCheck.pos.y == block.pos.y)
                {
                    block.visibleFaces.push_back(BlockFaces::Back);
                }
                else if (zDiff == -1 && blockCheck.pos.x == block.pos.x && blockCheck.pos.y == block.pos.y)
                {
                    block.visibleFaces.push_back(BlockFaces::Front);
                }

            }
        }
    }
}
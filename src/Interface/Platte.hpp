#ifndef PLATTE_HPP_INCLUDED
#define PLATTE_HPP_INCLUDED

#include <basic.h>

class Platte{
    private:
    /**
    *Pattern:
    *boarderonBG == false
    *|-----------|-----------|-----------|
    *|  edge[0]  | border[0] |  edge[1]  |
    *|-----------|-----------|-----------|
    *|           |           |           |
    *| border[3] |    bg     | border[1] |
    *|           |           |           |
    *|-----------|-----------|-----------|
    *|  edge[3]  | border[2] |  edge[2]  |
    *|-----------|-----------|-----------|
    *
    *boarderonBG == true
    *|--edge[0]--|-border[0]-|--edge[1]--|
    *|bo |                           |bo |
    *|rd |           bg              |rd |
    *|er |                           |er |
    *|[3]|                           |[1]|
    *|--edge[3]--|-border[2]-|--edge[2]--|
    */

    F2C::Sprite edge[4];
    F2C::Plane border[4];
    F2C::Plane bg;

    public:
    int x,y,z;
    F2C::uint width,height;
    F2C::Color color;
    bool stretchBG; ///< is BG stretch (zoom) else endless
    bool show;
    bool borderonBG; ///< border and edges over BG
    static int addMoveBG; ///< (if borderonBG == true),distance of border from the BG (pixel)

    Platte();

    /**
    *@param bitmap Border and Edges
    *@param widthEdge width of an edge
    *@param heightEdge height of an edge
    *@param widthBorderLeft width of an left/right border
    *@param heightBorderLeft height of an left/right border
    *@param widthBorderTop width of an top/bottom border
    *@param heightBorderTop height of an top/bottom border
    *@brief load Border and Edges from bitmap
    */
    void loadFrame(const F2C::Bitmap& bitmap,
                    F2C::uint widthEdge,F2C::uint heightEdge,
                    F2C::uint widthBorderLeft,F2C::uint heightBorderLeft,
                    F2C::uint widthBorderTop,F2C::uint heightBorderTop);

    /**
    *@param bitmap BG
    *@param x x-coord of BG
    *@param y y-coord of BG
    *@param widthBG width of BG
    *@param heightBG height of BG
    *@brief copy BG(Bitmap) into BG Sprite
    */
    void loadBG(const F2C::Bitmap& bitmap,int x,int y,F2C::uint widthBG,F2C::uint heightBG);

    /**
    *@param bitmap Border,Edges and BG
    *@param widthEdge width of an edge
    *@param heightEdge height of an edge
    *@param widthBorderLeft width of an left/right border
    *@param heightBorderLeft height of an left/right border
    *@param widthBorderTop width of an top/bottom border
    *@param heightBorderTop height of an top/bottom border
    *@param widthBG width of BG
    *@param heightBG height of BG
    *@brief load Border,Edges and BG from bitmap (look pattern)
    */
    void loadPlatte(const F2C::Bitmap& bitmap,
                    F2C::uint widthEdge,F2C::uint heightEdge,
                    F2C::uint widthBorderLeft,F2C::uint heightBorderLeft,
                    F2C::uint widthBorderTop,F2C::uint heightBorderTop,
                    F2C::uint widthBG,F2C::uint heightBG);

    /**
    *@param filename filename of Image with Border,Edges and BG
    *@param widthEdge width of an edge
    *@param heightEdge height of an edge
    *@param widthBorderLeft width of an left/right border
    *@param heightBorderLeft height of an left/right border
    *@param widthBorderTop width of an top/bottom border
    *@param heightBorderTop height of an top/bottom border
    *@param widthBG width of BG
    *@param heightBG height of BG
    *@brief load Border,Edges and BG from bitmap (look pattern)
    */
    void loadPlatte(std::string filename,
                    F2C::uint widthEdge,F2C::uint heightEdge,
                    F2C::uint widthBorderLeft,F2C::uint heightBorderLeft,
                    F2C::uint widthBorderTop,F2C::uint heightBorderTop,
                    F2C::uint widthBG,F2C::uint heightBG);
    /**
    *@brief clear Border,Edges and BG (empty Bitmap)
    */
    void clearPlatte();

    /**
    *@brief clear BG (empty Bitmap)
    */
    void clearBG();

    /**
    *@brief clear Border and Edges (empty Bitmap)
    */
    void clearFrame();

    void setViewport(F2C::Viewport* viewport);

    F2C::Rect getEdgesSize() const;
    F2C::Rect getBGSize() const;

    /**
    *@param get target reference variable
    *@brief get Size of Border
    *[0] = top
    *[1] = right
    *[2] = buttom
    *[3] = left
    */
    void getBorderSize(std::vector<F2C::Rect>& get) const;

    void render();

};

#endif // PLATTE_HPP_INCLUDED

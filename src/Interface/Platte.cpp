#include "Platte.hpp"

int Platte::addMoveBG = 2;

Platte::Platte():
    x(0),
    y(0),
    z(0),
    width(0),
    height(0),
    color(255,255,255,255),
    stretchBG(true),
    show(true),
    borderonBG(true)
{}

void Platte::loadFrame(const F2C::Bitmap& bitmap,
                    F2C::uint widthEdge,F2C::uint heightEdge,
                    F2C::uint widthBorderLeft,F2C::uint heightBorderLeft,
                    F2C::uint widthBorderTop,F2C::uint heightBorderTop)
{
    /**
    *|---------|---------------|---------|
    *| edge[0] |   border[0]   | edge[1] |
    *|---------|---------------|---------|
    *| bor     |               | bor     |
    *| der[3]  |               | der[1]  |
    *|---------|---------------|---------|
    *| edge[3] |   border[2]   | edge[2] |
    *|---------|---------------|---------|
    */
    F2C::Bitmap bitmapEdges[4];
    for(size_t i = 0;i < 4;++i)
        bitmapEdges[i].newBitmap(widthEdge,heightEdge);

    F2C::Bitmap bitmapBorder[4];
    bitmapBorder[0].newBitmap(widthBorderTop,heightBorderTop);
    bitmapBorder[1].newBitmap(widthBorderLeft,heightBorderLeft);
    bitmapBorder[2].newBitmap(widthBorderTop,heightBorderTop);
    bitmapBorder[3].newBitmap(widthBorderLeft,heightBorderLeft);

    //up-left
    bitmapEdges[0].blt(bitmap,0,0,
                        0,0,
                        widthEdge,heightEdge);
    //up-right
    bitmapEdges[1].blt(bitmap,0,0,
                        widthEdge+widthBorderTop,0,
                        widthEdge,heightEdge);
    //down-right
    bitmapEdges[2].blt(bitmap,0,0,
                            widthEdge+widthBorderTop,
                            heightEdge+heightBorderLeft,
                            widthEdge,heightEdge);
    //down-left
    bitmapEdges[3].blt(bitmap,0,0,
                            0,heightEdge+heightBorderLeft,
                            widthEdge,heightEdge);

    //top
    bitmapBorder[0].blt(bitmap,0,0,
                        widthEdge,0,
                        widthBorderTop,heightBorderTop);
    //right
    bitmapBorder[1].blt(bitmap,0,0,
                        widthEdge+widthBorderTop,heightEdge,
                        widthBorderLeft,heightBorderLeft);

    //down
    bitmapBorder[2].blt(bitmap,0,0,
                        widthEdge,heightEdge+heightBorderLeft,
                        widthBorderTop,heightBorderTop);
    //left
    bitmapBorder[3].blt(bitmap,0,0,
                        0,heightEdge,
                        widthBorderLeft,heightBorderLeft);

    for(size_t i = 0;i < 4;++i){
        this->edge[i].setBitmap(&bitmapEdges[i]);
        this->border[i].setBitmap(&bitmapBorder[i]);
    }
}

void Platte::loadBG(const F2C::Bitmap& bitmap,int x,int y,F2C::uint widthBG,F2C::uint heightBG){
    F2C::Bitmap bitmapBG (widthBG,heightBG);
    //bg
    bitmapBG.blt(bitmap,0,0,
                        x,y,
                        widthBG,heightBG);
    this->bg.setBitmap(&bitmapBG);
}

void Platte::loadPlatte(const F2C::Bitmap& bitmap,
                F2C::uint widthEdge,F2C::uint heightEdge,
                F2C::uint widthBorderLeft,F2C::uint heightBorderLeft,
                F2C::uint widthBorderTop,F2C::uint heightBorderTop,
                F2C::uint widthBG,F2C::uint heightBG)

{
    this->loadFrame(bitmap,
                    widthEdge,heightEdge,
                    widthBorderLeft,heightBorderLeft,
                    widthBorderTop,heightBorderTop);
    this->loadBG(bitmap,widthEdge,heightEdge,widthBG,heightBG);
}

void Platte::loadPlatte(std::string filename,
                F2C::uint widthEdge,F2C::uint heightEdge,
                F2C::uint widthBorderLeft,F2C::uint heightBorderLeft,
                F2C::uint widthBorderTop,F2C::uint heightBorderTop,
                F2C::uint widthBG,F2C::uint heightBG)
{
    F2C::Bitmap bitmap;
    try{
        bitmap.loadFile(filename);
    }catch(F2C::LogError& er){
        SETLOGERROR(er,er.getError());
        er.writeError();
    }
    this->loadPlatte(bitmap,
                widthEdge,heightEdge,
                widthBorderLeft,heightBorderLeft,
                widthBorderTop,heightBorderTop,
                widthBG,heightBG);
}

void Platte::clearFrame(){
    for(size_t i = 0;i < 4;++i){
        this->edge[i].setBitmap(NULL);
        this->border[i].setBitmap(NULL);
    }
}

void Platte::clearBG(){
    this->bg.setBitmap(NULL);
}

void Platte::clearPlatte(){
    this->clearFrame();
    this->clearBG();
}

void Platte::setViewport(F2C::Viewport* viewport){
    for(size_t i = 0;i < 4;++i){
        this->border[i].setViewport(viewport);
        this->edge[i].setViewport(viewport);
    }
    this->bg.setViewport(viewport);
}

F2C::Rect Platte::getEdgesSize() const {
    return F2C::Rect (0,0,this->edge[0].getTexWidth(),this->edge[0].getTexHeight());
}

F2C::Rect Platte::getBGSize() const {
    F2C::Rect edgeSize = this->getEdgesSize();

    int wtopbg = static_cast<int>(this->width) - (edgeSize.width * ((this->borderonBG)? 0 : 2));
    int hleftbg = static_cast<int>(this->height) - (edgeSize.height * ((this->borderonBG)? 0 : 2));
    wtopbg -= ((this->borderonBG)? addMoveBG*2 : 0);
    hleftbg -= ((this->borderonBG)? addMoveBG*2 : 0);

    F2C::uint BGWidth = std::max(0,wtopbg);
    F2C::uint BGHeight = std::max(0,hleftbg);

    return F2C::Rect (0,0,BGWidth,BGHeight);
}

void Platte::getBorderSize(std::vector<F2C::Rect>& get) const{
    get.resize(4);

    F2C::Rect edgeSize = this->getEdgesSize();

    int wtop = static_cast<int>(this->width) - edgeSize.width*2;
    int hleft = static_cast<int>(this->height) - edgeSize.height*2;

    F2C::uint borderWidthTop = std::max(0,wtop);
    F2C::uint borderHeightLeft = std::max(0,hleft);

    get[0].set(0,0,borderWidthTop,this->border[0].getTexHeight());
    get[1].set(0,0,this->border[1].getTexWidth(),borderHeightLeft);
    get[2].set(0,0,borderWidthTop,this->border[2].getTexHeight());
    get[3].set(0,0,this->border[3].getTexWidth(),borderHeightLeft);
}

void Platte::render(){
    if(!this->show)
        return;
    if(this->color.alpha == 0)
        return;
    if(this->width < 1 || this->height < 1)
        return;

    std::vector<F2C::Rect> borderSize;
    this->getBorderSize(borderSize);

    F2C::Rect BG = this->getBGSize();

    for(size_t i = 0;i < 4;++i)
        this->border[i].src_rect = borderSize[i];

    if(this->stretchBG){
        double zoomfw = static_cast<double>(BG.width)/this->bg.getTexWidth();
        double zoomfh = static_cast<double>(BG.height)/this->bg.getTexHeight();
        this->bg.zoom_x = std::max(1.0,zoomfw);
        this->bg.zoom_y = std::max(1.0,zoomfh);
        this->bg.src_rect.set(0,0,0,0);
        if(zoomfw < 1.0f)
            this->bg.src_rect.width = BG.width;
        if(zoomfh < 1.0f)
            this->bg.src_rect.height = BG.height;
    }else{
        this->bg.zoom_x = 1.0f;
        this->bg.zoom_y = 1.0f;
        this->bg.src_rect.set(0,0,BG.width,BG.height);
    }

    this->edge[0].x = this->x;
    this->edge[0].y = this->y;

    this->bg.x = this->x + ((!this->borderonBG)? this->edge[0].getTexWidth() : addMoveBG);
    this->bg.y = this->y + ((!this->borderonBG)? this->edge[0].getTexHeight() : addMoveBG);

    this->border[0].x = this->x+this->edge[0].getTexWidth();
    this->border[0].y = this->y;

    this->edge[1].x = this->x+this->edge[0].getTexWidth()+this->border[0].src_rect.width;
    this->edge[1].y = this->y;

    this->border[1].x = this->x+this->edge[0].getTexWidth()+this->border[0].src_rect.width;
    this->border[1].y = this->y+this->edge[0].getTexHeight();

    this->edge[2].x = this->x+this->edge[0].getTexWidth()+this->border[0].src_rect.width;
    this->edge[2].y = this->y+this->edge[0].getTexHeight()+this->border[3].src_rect.height;

    this->border[2].x = this->x+this->edge[0].getTexWidth();
    this->border[2].y = this->y+this->edge[0].getTexHeight()+this->border[3].src_rect.height;

    this->edge[3].x = this->x;
    this->edge[3].y = this->y+this->edge[0].getTexHeight()+this->border[3].src_rect.height;

    this->border[3].x = this->x;
    this->border[3].y = this->y+this->edge[0].getTexHeight();

    for(size_t i = 0;i < 4;++i){
        this->edge[i].z = this->z;
        this->border[i].z = this->z;
        this->edge[i].setColor(this->color);
        this->border[i].setColor(this->color);
    }
    this->bg.z = z;
    this->bg.setColor(this->color);

    this->bg.render();
    for(size_t i = 0;i < 4;++i)
        this->border[i].render();
    for(size_t i = 0;i < 4;++i)
        this->edge[i].render();
}

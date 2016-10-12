#ifndef __F2C_BITMAP_HPP_INCLUDED
#define __F2C_BITMAP_HPP_INCLUDED

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <Fantasy2C/Basic.hpp>
#include <Fantasy2C/Rect.hpp>
#include <Fantasy2C/Color.hpp>
#include <Fantasy2C/GameError.hpp>


template class DLL std::allocator< F2C::ubyte >;
template class DLL std::vector< F2C::ubyte, std::allocator<F2C::ubyte> >;

namespace F2C{

/**
*@class Bitmap
*@brief Loading image files. \n
*Automatically creates a pixel array with a quadratic power of 2 (32x32, 64x64 ,..., 512x512 ,...) \n
*and paste the loaded image into the pixel array. \n
*DevIL Supported Formats: \n
*Load: \n
*@brief  *Windows Bitmap - .bmp \n
*@brief  *Dr. Halo - .cut \n
*@brief  *Multi-PCX - .dcx \n
*@brief  *Dicom - .dicom, .dcm \n
*@brief  *DirectDraw Surface - .dds \n
*@brief  *OpenEXR - .exr \n
*@brief  *Flexible Image Transport System - .fits, .fit \n
*@brief  *Heavy Metal: FAKK 2 - .ftx \n
*@brief  *Radiance High Dynamic - .hdr \n
*@brief  *Macintosh icon - .icns \n
*@brief  *Windows icon/cursor - .ico, .cur \n
*@brief  *Interchange File Format - .iff \n
*@brief  *Infinity Ward Image - .iwi \n
*@brief  *Graphics Interchange Format - .gif \n
*@brief  *Jpeg - .jpg, .jpe, .jpeg \n
*@brief  *Jpeg 2000 - .jp2 \n
*@brief  *Interlaced Bitmap - .lbm \n
*@brief  *Homeworld texture - .lif \n
*@brief  *Half-Life Model - .mdl \n
*@brief  *Palette - .pal \n
*@brief  *Kodak PhotoCD - .pcd \n
*@brief  *ZSoft PCX - .pcx \n
*@brief  *Softimage PIC - .pic \n
*@brief  *Portable Network Graphics - .png \n
*@brief  *Portable Anymap - .pbm, .pgm, .pnm, .pnm \n
*@brief  *Alias | Wavefront - .pix \n
*@brief  *Adobe PhotoShop - .psd \n
*@brief  *PaintShop Pro - .psp \n
*@brief  *Pixar - .pxr \n
*@brief  *Raw data - .raw \n
*@brief  *Homeworld 2 Texture - .rot \n
*@brief  *Silicon Graphics - .sgi, .bw, .rgb, .rgba \n
*@brief  *Creative Assembly Texture - .texture \n
*@brief  *Truevision Targa - .tga \n
*@brief  *Tagged Image File Format - .tif \n
*@brief  *Gamecube Texture - .tpl \n
*@brief  *Unreal Texture - .utx \n
*@brief  *Quake 2 Texture - .wal \n
*@brief  *Valve Texture Format - .vtf \n
*@brief  *HD Photo - .wdp, .hdp \n
*@brief  *X Pixel Map - .xpm \n
*@brief  *Doom graphics \n
*@brief \n
*@brief Save: \n
*@brief  *Windows Bitmap - .bmp \n
*@brief  *DirectDraw Surface - .dds \n
*@brief  *OpenEXR - .exr \n
*@brief  *C-style Header - .h \n
*@brief  *Radiance High Dynamic - .hdr \n
*@brief  *Jpeg - .jpg \n
*@brief  *Jpeg 2000 - .jp2 \n
*@brief  *Palette - .pal \n
*@brief  *ZSoft PCX - .pcx \n
*@brief  *Portable Network Graphics - .png \n
*@brief  *Portable Anymap - .pbm, .pgm, .pnm, .pnm \n
*@brief  *Adobe PhotoShop - .psd \n
*@brief  *Raw data - .raw \n
*@brief  *Silicon Graphics - .sgi, .bw, .rgb, .rgba \n
*@brief  *Truevision Targa - .tga \n
*@brief  *Tagged Image File Format - .tif \n
*@brief  *Valve Texture Format - .vtf \n
*/

class DLL Bitmap{
	private:
		std::string filename;
		ubyte* pixels;
		uint width;
		uint height;
		uint create_width;
		uint create_height;
		uint po2_size;
		bool is_changed;
		Image::ImageType image_type;
		Image::DataFormat data_format;
		uint bits;
		size_t psize;

		bool loadImageintoBitmap(GLuint image_id,std::string filename,Image::ImageType type,LogError* error);
		bool loadFileintoBitmap(GLuint image_id,FILE* file,Image::ImageType type,LogError* error);
		bool loadFileintoBitmap(GLuint image_id,std::istream& file,Image::ImageType type,LogError* error);

		static void make_image(GLuint* image_id,Image::DataFormat dataformat);
		static void make_image(GLuint* image_id,Image::DataFormat dataformat,uint width,uint height);
		static void make_image(GLuint* image_id,Image::DataFormat dataformat,uint width,uint height,uint8 r,uint8 g,uint8 b,uint8 a);
		static void blt_image(const ubyte* src_data,
                            int src_xstart, int src_ystart,
                            uint src_arraywidth,
                            uint src_bytepp,
                            uint src_bitmapwidth,uint src_bitmapheight,

                            ubyte* dst_data,
                            int dst_xstart, int dst_ystart,
                            uint dst_arraywidth,
                            uint dst_bytepp,
                            uint dst_bitmapwidth,uint dst_bitmapheight,

                            uint width, uint height,
                            bool blend, uint8 alpha);

        static bool initil;
        static void initDevIL();

        static void BuildFont(Rect* outarray,size_t outarraysize,
                       const Bitmap& bitmapfont,
                       uint charpw,uint charph,uint8 alphatolerance);

	public:
        /**
        *@param src_data Pixles source array
        *@param src_xstart Source X coordinate
        *@param src_ystart Source Y coordinate
        *@param src_bitmapwidth Width of source array
        *@param src_bitmapheight Height of source array
        *@param src_bytepp Byte per pixels of source array
        *@param dst_data Pixles destination array
        *@param dst_xstart Destination X coordinate
        *@param dst_ystart Destination Y coordinate
        *@param dst_bitmapwidth Width of destination array
        *@param dst_bitmapheight Height of destinationarray
        *@param dst_bytepp Byte per pixels of destination array
        *@param width Width of the copy area.
        *@param height Height of the copy area.
        *@param blend use Alphablending
        *@param alpha Alpha value of the inserted image.(Alphablending)
        *@brief Copy a specific area of source array into destination array.(array[bitmapwidth * bitmapheight * bytepp])
        */
        static void bltPixels(const ubyte* src_data,
                            int src_xstart, int src_ystart,
                            uint src_bitmapwidth,uint src_bitmapheight,
                            uint src_bytepp,

                            ubyte* dst_data,
                            int dst_xstart, int dst_ystart,
                            uint dst_bitmapwidth,uint dst_bitmapheight,
                            uint dst_bytepp,

                            uint width, uint height,
                            bool blend, uint8 alpha);

		Bitmap(); ///< Default constructor
		virtual ~Bitmap(); ///< Delete the pixels from memory.
		Bitmap(const Bitmap& copy); ///< Copy constructor
		Bitmap& operator= (const Bitmap& copy); ///< Assignment operator with deep copy.

		/**
		*@param width Width of Bitmap
		*@param height Height of Bitmap
		*@brief Creates an empty bitmap with the specified height and width.
		*/
		Bitmap(uint width,uint height);

		/**
		*@param filename Image filename
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image File.
		*/
		Bitmap(std::string filename);

		/**
		*@param filename Image filename
		*@param type Image Datatype
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image File.
		*/
		Bitmap(std::string filename,Image::ImageType type);

		/**
		*@param stream File Stream
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image from Memory.
		*/
		Bitmap(FILE* stream);
		/**
		*@param stream File Stream
		*@param type Image Datatype
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image from Memory.
		*/
		Bitmap(FILE* stream,Image::ImageType type);

		/**
		*@param stream File Stream
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image from Memory.
		*/
		Bitmap(std::istream& stream);
		/**
		*@param stream File Stream
		*@param type Image Datatype
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image from Memory.
		*/
		Bitmap(std::istream& stream,Image::ImageType type);

		/**
		*@param pixels Pixelarray
		*@param width Image width
		*@param height Image height
		*@param bpp Bytes per Pixel
		*@param format Pixel Data Format
		*@brief Load an pixelarray into Bitmap
		*/
		Bitmap(const ubyte* pixels,uint width,uint height,uint bpp,Image::DataFormat format);
		/**
		*@param pixels Pixelarray
		*@param width Image width
		*@param height Image height
		*@param bpp Bytes per Pixel
		*@param format Pixel Data Format
		*@brief Load an pixelarray into Bitmap
		*/
		Bitmap(const std::vector<ubyte>& pixels,uint width,uint height,uint bpp,Image::DataFormat format);

		/**
		*@param stream File Stream
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image from Memory.
		*/
		void loadFile(FILE* stream);
		/**
		*@param stream File Stream
		*@param type Image Datatype
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image from Memory.
		*/
		void loadFile(FILE* stream,Image::ImageType type);

		/**
		*@param stream File Stream
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image from Memory.
		*/
		void loadFile(std::istream& stream);
		/**
		*@param stream File Stream
		*@param type Image Datatype
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image from Memory.
		*/
		void loadFile(std::istream& stream,Image::ImageType type);

        /**
		*@param filename Image filename
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image File.
		*/
		void loadFile(std::string filename);

		/**
		*@param filename Image filename
		*@param type Image Datatype
		*@exception LogError, If the file can not be loaded.
		*@brief Load an Image File.
		*/
		void loadFile(std::string filename,Image::ImageType type);

		/**
		*@param width Width of Bitmap
		*@param height Height of Bitmap
		*@brief Creates an empty bitmap with the specified height and width.
		*/
		void newBitmap(uint width,uint height);

		/**
		*@param pixels Pixelarray
		*@param width Image width
		*@param height Image height
		*@param bpp Bytes per Pixel
		*@param format Pixel Data Format
		*@brief Load an pixelarray into Bitmap
		*/
		void loadPixelArray(const ubyte* pixels,uint width,uint height,uint bpp,Image::DataFormat format);
		/**
		*@param pixels Pixelarray
		*@param width Image width
		*@param height Image height
		*@param bpp Bytes per Pixel
		*@param format Pixel Data Format
		*@brief Load an pixelarray into Bitmap
		*/
		void loadPixelArray(const std::vector<ubyte>& pixels,uint width,uint height,uint bpp,Image::DataFormat format);

		void clear(); ///< Set all pixels on 0.

        /**
        *@param Src Bitmap source
        *@param destX Destination X coordinate
        *@param destY Destination Y coordinate
        *@param srcX Source X coordinate
        *@param srcY Source Y coordinate
        *@param width Width of the copy area.
        *@param height Height of the copy area.
        *@brief Copy a specific area of an image(Bitmap) in the Bitmap
        */
		void blt(const Bitmap& Src,int destX, int destY,int srcX,int srcY, uint width, uint height);

		/**
        *@param Src Bitmap source
        *@param destX Destination X coordinate
        *@param destY Destination Y coordinate
        *@param srcX Source X coordinate
        *@param srcY Source Y coordinate
        *@param width Width of the copy area.
        *@param height Height of the copy area.
        *@param alpha Alpha value of the inserted image.
        *@brief Copy a specific area of an image(Bitmap) in the Bitmap.
        */
		void blt(const Bitmap& Src,int destX, int destY,int srcX,int srcY, uint width, uint height,uint8 alpha);

		/**
        *@param Src Bitmap source
        *@param destX Destination X coordinate
        *@param destY Destination Y coordinate
        *@brief Copies an entire image(Bitmap) in the Bitmap.
        */
		void bltFull(const Bitmap& Src,int destX, int destY);

		/**
        *@param Src Bitmap source
        *@param destX Destination X coordinate
        *@param destY Destination Y coordinate
        *@param alpha Alpha value of the inserted image.
        *@brief Copies an entire image(Bitmap) in the Bitmap.
        */
		void bltFull(const Bitmap& Src,int destX, int destY,uint8 alpha);

        /**
        *@param x X coordinate
        *@param y Y coordinate
        *@param r Red
        *@param g Green
        *@param b Blue
        *@param a Alpha
        *@brief setMethode: set a pixel.
        */
		void setPixel(uint x,uint y, uint8 r,uint8 g,uint8 b,uint8 a);
		/**
        *@param x X coordinate
        *@param y Y coordinate
        *@param color Color
        *@brief setMethode: set a pixel.
        */
		void setPixel(uint x,uint y, Color color);

		/**
		*@param hue Hue (0-360) @brief setMethode: Hue. (HSV-Color Models)
		*@image html colorcircle.jpg
		*/
		void setHue(uint hue);
		/**
		*@param s Saturation @brief setMethode: Saturation. (HSV-Color Models)
		*@image html saturation.jpg
		*/
		void setSaturation(uint8 s);
		/**
		*@param v Value @brief setMethode: Value. (HSV-Color Models)
		*@image html Brightness.jpg
		*/
		void setValue(uint8 v);

        /**
        *@param x X coordinate
        *@param y Y coordinate
        *@param width Width
        *@param height Height
        *@param r Red
        *@param g Green
        *@param b Blue
        *@param a Alpha
        *@brief Fill an area with color.
        */
		void fillRect(int x,int y,uint width,uint height,uint8 r,uint8 g,uint8 b,uint8 a);
		/**
        *@param rect Area
        *@param color Color
        *@brief Fill an area with color.
        */
		void fillRect(const Rect &rect,const Color &color);

		/**
        *@param x X coordinate
        *@param y Y coordinate
        *@param width Width
        *@param height Height
        *@param r Red
        *@param g Green
        *@param b Blue
        *@param a Alpha
        *@brief Clear an area (Set pixels on 0).
        */
		void clearRect(int x,int y,uint width,uint height,uint8 r,uint8 g,uint8 b,uint8 a);
		/**
        *@param rect Area
        *@param color Color
        *@brief Clear an area (Set pixels on 0).
        */
		void clearRect(const Rect &rect,const Color &color);

		/**
        *@param width new Width
        *@param height new Height
        *@brief Scales the bitmap.
        */
		void scale(uint width,uint height);

        /**
        *@param filename Image Filename @brief Save as image File.
        */
		void save(std::string filename) const;

		/**
        *@param filename Image Filename
        *@param type Datatype
        *@brief Save as image File.
        */
		void save(std::string filename,Image::ImageType type) const;

        /**
        *@param x X coordinate
        *@param y Y coordinate
        *@brief getMethode: Color of Pixel
        */
		Color getPixel(uint x,uint y) const;

		const ubyte* getPixels() const; ///< getMethode: Pointer from the pixel buffer, pixels [F2C::nextPowerof2(std::max<uint>(width, height)) * F2C::nextPowerof2(std::max<uint>(width, height)) * color depth (in bytes)].
		ubyte* getPixels(); ///< getMethode: Pointer from the pixel buffer, pixels [F2C::nextPowerof2(std::max<uint>(width, height)) * F2C::nextPowerof2(std::max<uint>(width, height)) * color depth (in bytes)].
		std::string getFilename() const; ///< getMethode: Image filename
		uint getWidth() const; ///< getMethode: Width of Bitmap
		uint getHeight() const; ///< getMethode: Height of Bitmap
		uint getCreateWidth() const; ///< getMethode: Width of the loaded image or originally created bitmap.
		uint getCreateHeight() const; ///< getMethode: Height of the loaded image or originally created bitmap.
		uint getPixelsWidth() const; ///< getMethode: Width (or height) of the pixel array: F2C::nextPowerof2(std::max<uint>(width, height)).
		Image::ImageType getImageType() const; ///< getMethode: File Format
		Image::DataFormat getDataFormat() const; ///< getMethode: Pixel data format
		uint getBits() const; ///< getMethode: Color depth (in bits)
		uint getBytes() const; ///< getMethode: Color depth (in Byte)
		Rect getRect() const; ///< getMethode: Size of bitmap, (0,0, width, height).
		size_t getPixelsSize() const; ///< getMethode: Size of pixel array
		bool isChanged() const; ///< getMethode: Is Bitmap changed, like setPixel,scale,blt,fillRect,...

		friend std::ostream& operator<<(std::ostream &out,const Bitmap& obj);
        friend std::istream& operator>>(std::istream &in, Bitmap& obj);
};

/**
*@param out Output stream
*@param obj Object
*@brief Write the Object into output stream.
*/
std::ostream& DLL operator<<(std::ostream &out,const Bitmap& obj);

/**
*@param in Input stream
*@param obj Object
*@brief Read the Object from input stream.
*/
std::istream& DLL operator>>(std::istream &in, Bitmap& obj);

}

#endif


#include "common_Video.h"

namespace common {

Video::Video(){

}

Video::Video(const std::string& rutaArchivo):capturasVideo(rutaArchivo)  {}


bool Video::setearSecuenciaDeImagenes(std::string templateImagenes){
	capturasVideo.open(templateImagenes);
	return this->esValido();
}

bool Video::esValido()const{
	return capturasVideo.isOpened();
}

void Video::capturasPeriodicasVideo(std::list<const Imagen>& listaImagenes, double periodoEnMinutos)const{
	/*double fps = capturasVideo.get(CV_CAP_PROP_FPS);
	unsigned long int cantidadDeFrames =  capturasVideo.get(CV_CAP_PROP_FRAME_COUNT);
	double duracionTotalEnMinutos = (cantidadDeFrames/(fps*60));
*/
}

void Video::mostrarVideo(double fps){
	using namespace cv;
	Mat image;
	namedWindow("Image sequence | press ESC to close", WINDOW_KEEPRATIO);

	while (true){
		// Read in image from sequence
		capturasVideo >> image;

		// If no image was retrieved -> end of sequence
		if(image.empty())
		{
			std::cout << "End of Sequence" << std::endl;
			capturasVideo.set(CAP_PROP_POS_MSEC,0);
			continue;
		}

		imshow("Image sequence | press ESC to close", image);

		char key = (char)waitKey(1000/fps); //delay N millis, usually long enough to display and capture input

		switch (key) {
		case 'q':
			destroyAllWindows();
			return;
		case 27: //escape key
			destroyAllWindows();
			return;
		case ' ': //
			while (true){
				switch((char)waitKey(0)){
				case ' ':
					break;
				case 27:
					destroyAllWindows();
					return;
				}
			}
		}

	}
}


} /* namespace common */

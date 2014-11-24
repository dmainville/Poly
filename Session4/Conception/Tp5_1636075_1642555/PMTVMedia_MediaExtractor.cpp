///////////////////////////////////////////////////////////
//  PMTVMedia_MediaExtractor.cpp
//  Implementation of the Class PMTVMedia_MediaExtractor
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVMedia_MediaExtractor.h"
#include "PMTVCodec/PMTVCodec_CodecFactory.h"
#include "PMTVCodec/PMTVCodec_CodecInterface.h"

//-----------------------------------------------------------------------------
// std::vector<PMTVMedia_Frame> PMTVMedia_MediaExtractor::extractFrame(unsigned int startFrame,unsigned int endFrame)
// unsigned int startFrame : # trame de début
// unsigned int endFrame   : # trame de fin
// std::vector<PMTVMedia_Frame> : Vecteur de trames décodées
// Extrait un certain nombre de trames à partir du conteneur avec le bon décodeur et retourne
// les trames.
//-----------------------------------------------------------------------------
std::vector<PMTVMedia_Frame> PMTVMedia_MediaExtractor::extractFrame(unsigned int startFrame,unsigned int endFrame)
{
    std::vector<PMTVMedia_Frame> extractedFrame;
    // À compléter...
    // RAPPEL : Utilisez la version SINGLETON de l'usine à codecs
	PMTVCodec_CodecFactory* factory = PMTVCodec_CodecFactory::getInstance();
	PMTVCodec_InterfaceType type = m_mediaContainer->getCodecCode();
	PMTVCodec_CodecInterface* codec = factory->getCodecInterface(type);

	if(!codec)
		return extractedFrame;

	if(m_mediaContainer->getNumberOfFrame() < endFrame)
		return extractedFrame;

	if(startFrame > endFrame)	
	{
		unsigned int temp = startFrame;
		startFrame = endFrame;
		endFrame = temp;
	}

	m_mediaContainer->setFrameExtractionPosition(startFrame);
	for(int i=startFrame; i<=endFrame; i++)
	{
		//Size?
		//Buffer?
		void* buffer;
		size_t size;
		m_mediaContainer->extractNextFrame(&buffer,size);

		void* trameDecode;
		codec->decode(buffer,size,&trameDecode,size);

		PMTVMedia_Frame *f = new PMTVMedia_Frame(trameDecode,size);
		extractedFrame.push_back(*f);
	}

	//

	


    return extractedFrame;
}

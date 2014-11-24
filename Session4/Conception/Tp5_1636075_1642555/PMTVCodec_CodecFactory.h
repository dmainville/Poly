///////////////////////////////////////////////////////////
//  PMTVCodec_CodecFactory.h
//  Implementation of the Class PMTVCodec_CodecFactory
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#ifndef PMTV_CODEC_CODEC_FACTORY_H
#define PMTV_CODEC_CODEC_FACTORY_H

class PMTVCodec_CodecInterface;

#include "PMTVCodec_InterfaceType.h"
#include <map>

//
// Classe PMTVCodec_CodecFactory
//
// Construit, initialise et contient les interfaces des encodeurs/décodeurs
// utilisé par PMTV. (codec)
//
//
class PMTVCodec_CodecFactory
{
private:
    std::map<PMTVCodec_InterfaceType,PMTVCodec_CodecInterface*> m_codecMap; // Map associatif codecCode-Interface Codec
	
	PMTVCodec_CodecFactory();
	static PMTVCodec_CodecFactory* instance;
	PMTVCodec_CodecFactory& operator= (const PMTVCodec_CodecFactory&){}
    PMTVCodec_CodecFactory (const PMTVCodec_CodecFactory&){}

protected:
    // Méthodes de construction / initialisation
    PMTVCodec_CodecInterface* createMPEG4Interface();
    PMTVCodec_CodecInterface* createIndeoInterface();
    PMTVCodec_CodecInterface* createRawDataInterface();

public:
    // Constructeur & Destructeur
	static PMTVCodec_CodecFactory* getInstance();
    ~PMTVCodec_CodecFactory();

    // Accesseurs
    PMTVCodec_CodecInterface* getCodecInterface(PMTVCodec_InterfaceType interfaceType);
    bool isCodecSupported(PMTVCodec_InterfaceType interfaceType);

    // :TEST:
    // NE PAS TOUCHER.
    friend class PMTVTest_MainTest;
};

#endif

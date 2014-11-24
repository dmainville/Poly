///////////////////////////////////////////////////////////
//  PMTVCodec_CodecFactory.cpp
//  Implementation of the Class PMTVCodec_CodecFactory
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
///////////////////////////////////////////////////////////

#include "PMTVCodec_CodecFactory.h"
#include "PMTVCodec_MPEG4CodecInterface.h"
#include "PMTVCodec_INDEOCodecInterface.h"
#include "PMTVCodec_RAWCodecInterface.h"

//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------
PMTVCodec_CodecFactory* PMTVCodec_CodecFactory::instance = 0;

PMTVCodec_CodecFactory::PMTVCodec_CodecFactory()
{
}

PMTVCodec_CodecFactory* PMTVCodec_CodecFactory::getInstance()
{
	if(!instance)
		instance = new PMTVCodec_CodecFactory();
    return instance;
}

//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------
PMTVCodec_CodecFactory::~PMTVCodec_CodecFactory()
{
	//Itérer à travers la map des codec disponible et les désalouer
	for(std::map<PMTVCodec_InterfaceType,PMTVCodec_CodecInterface*>::iterator it = m_codecMap.begin(); it != m_codecMap.end(); it++) {
		it->second->unloadCodec();
	}

	m_codecMap.clear();
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createMPEG4Interface()
// Construit et retourne l'interface MPEG4 avec paramètres par défaut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createMPEG4Interface()
{
    return new PMTVCodec_MPEG4CodecInterface();
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createIndeoInterface()
// Construit et retourne l'interface INDEO avec paramètres par défaut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createIndeoInterface()
{
	return new PMTVCodec_INDEOCodecInterface();
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createRawDataInterface()
// Construit et retourne l'interface RAW avec paramètres par défaut.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::createRawDataInterface()
{
	return new PMTVCodec_RAWCodecInterface();
}

//-----------------------------------------------------------------------------
// bool isCodecSupported(PMTVCodec_InterfaceType interfaceType)
// PMTVCodec_InterfaceType interfaceType : Code du CODEC
// Indique si oui ou non un codec est supporté (lire installé) par PMTV.
//-----------------------------------------------------------------------------
bool PMTVCodec_CodecFactory::isCodecSupported(PMTVCodec_InterfaceType interfaceType)
{
	std::map<PMTVCodec_InterfaceType,PMTVCodec_CodecInterface*>::iterator it = m_codecMap.find(interfaceType);
	if(it != m_codecMap.end())
	{
		return true;
	}
    return false;
}

//-----------------------------------------------------------------------------
// PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::getCodecInterface(PMTVCodec_InterfaceType interfaceType)
// PMTVCodec_InterfaceType interfaceType : 
//
// Récupère l'interface du codec en fonction du type demandé et construit l'interface avec paramètres par défauts
// si elle n'est pas disponible.
// Retourne 0 si l'interface demandée ne peut être construite.
//-----------------------------------------------------------------------------
PMTVCodec_CodecInterface* PMTVCodec_CodecFactory::getCodecInterface(PMTVCodec_InterfaceType interfaceType)
{
	if(isCodecSupported(interfaceType))
	{
		std::map<PMTVCodec_InterfaceType,PMTVCodec_CodecInterface*>::iterator it = m_codecMap.find(interfaceType);
		if(it != m_codecMap.end())
		{
			return it->second;
		}
	}
	else
	{
		//Créer le codec et l'ajouter à la map
		// PMTV supporte MPEG4, INDEO et RAW.
		PMTVCodec_CodecInterface* c;
		switch ( interfaceType )
		{
			case PMTVCODEC_MPEG4:
				c = createMPEG4Interface();
				break;
			case PMTVCODEC_INDEO:
				c = createIndeoInterface();
				break;
			case PMTVCODEC_RAW:
				c = createRawDataInterface();
				break;
			default:
				c = NULL;
		}

		if(c)
		{
			m_codecMap.insert(std::make_pair(interfaceType,c));
			return c;
		}
	}

    return 0;
}


///////////////////////////////////////////////////////////
//  PMTVMedia_MediaExtractor.h
//  Implementation of the Class PMTVMedia_MediaExtractor
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dub�
///////////////////////////////////////////////////////////

#ifndef PMTV_MEDIA_MEDIA_EXTRACTOR_H
#define PMTV_MEDIA_MEDIA_EXTRACTOR_H

class PMTVMedia_MediaDirector;

#include <list>
#include <vector>

#include "PMTVMedia_MediaContainer.h"
#include "PMTVMedia_Frame.h"

//
// Classe PMTVMedia_MediaExtractor
//
// Classe m�diatrice qui contr�le l'extraction des trames � partir des conteneurs.  Elles r�alisent la m�diation entre
// les conteneurs, les CODEC et les directeurs.
//
// La classe a le contr�le du d�bit d'extraction.  Les donn�es extraites sont ensuite donn�s
// � un d�codeur et finalement envoy� aux directeurs.
//
class PMTVMedia_MediaExtractor
{
private:
    unsigned int m_fps; // Trames / sec
    
    PMTVMedia_MediaContainer* m_mediaContainer; // Conteneur du m�dia � extraire
    std::vector<PMTVMedia_Frame> m_frameCache;  // Cache de trames
    std::list<PMTVMedia_MediaDirector*> m_directorList; // Directeurs

protected:
    void notifyFrameUpdate();      // Indique qu'une ou plusieurs trames sont disponibles
    void notifyResolutionChange(); // Indique un changement dans la r�solution du m�dia (vid�o)

public:
    // Constructeur & Destructeur
    PMTVMedia_MediaExtractor() : m_mediaContainer(0) {};
    ~PMTVMedia_MediaExtractor() {};

    // Accesseurs
    void setFPS(unsigned int fps)              { m_fps = fps;          }
    void setMedia(PMTVMedia_MediaContainer* c) { m_mediaContainer = c; }
    
    void clearFrameCache() { m_frameCache.clear(); }

    // Accesseurs du cache de trames (int�gral, copie)
    std::vector<PMTVMedia_Frame> getFrameCache() { return m_frameCache; }
    std::vector<PMTVMedia_Frame> getFrameCacheCopy();

    // Contr�le piste
    // � venir

    // Extraction
    std::vector<PMTVMedia_Frame> extractFrame(unsigned int startFrame,unsigned int endFrame); // Extraction de trames born�es 
    
    // � venir
    // void startExtraction(PMTVMedia_Time start,PMTVMedia_Time end); // Extraction par limites de temps
    // void startExtraction(unsigned int chapter); // Extraction par chapitre
    // void stopExtraction();

    // Enregistrement / d�senregistrement de directeurs
    void registerDirector(PMTVMedia_MediaDirector* md);
    void unregisterDirector(PMTVMedia_MediaDirector* md);
    void clearDirectorList();
};

#endif

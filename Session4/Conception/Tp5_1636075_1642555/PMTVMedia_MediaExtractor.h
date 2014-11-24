///////////////////////////////////////////////////////////
//  PMTVMedia_MediaExtractor.h
//  Implementation of the Class PMTVMedia_MediaExtractor
//  Created on:      31-oct.-2010 15:20:25
//  Original author: David Dubé
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
// Classe médiatrice qui contrôle l'extraction des trames à partir des conteneurs.  Elles réalisent la médiation entre
// les conteneurs, les CODEC et les directeurs.
//
// La classe a le contrôle du débit d'extraction.  Les données extraites sont ensuite donnés
// à un décodeur et finalement envoyé aux directeurs.
//
class PMTVMedia_MediaExtractor
{
private:
    unsigned int m_fps; // Trames / sec
    
    PMTVMedia_MediaContainer* m_mediaContainer; // Conteneur du média à extraire
    std::vector<PMTVMedia_Frame> m_frameCache;  // Cache de trames
    std::list<PMTVMedia_MediaDirector*> m_directorList; // Directeurs

protected:
    void notifyFrameUpdate();      // Indique qu'une ou plusieurs trames sont disponibles
    void notifyResolutionChange(); // Indique un changement dans la résolution du média (vidéo)

public:
    // Constructeur & Destructeur
    PMTVMedia_MediaExtractor() : m_mediaContainer(0) {};
    ~PMTVMedia_MediaExtractor() {};

    // Accesseurs
    void setFPS(unsigned int fps)              { m_fps = fps;          }
    void setMedia(PMTVMedia_MediaContainer* c) { m_mediaContainer = c; }
    
    void clearFrameCache() { m_frameCache.clear(); }

    // Accesseurs du cache de trames (intégral, copie)
    std::vector<PMTVMedia_Frame> getFrameCache() { return m_frameCache; }
    std::vector<PMTVMedia_Frame> getFrameCacheCopy();

    // Contrôle piste
    // À venir

    // Extraction
    std::vector<PMTVMedia_Frame> extractFrame(unsigned int startFrame,unsigned int endFrame); // Extraction de trames bornées 
    
    // À venir
    // void startExtraction(PMTVMedia_Time start,PMTVMedia_Time end); // Extraction par limites de temps
    // void startExtraction(unsigned int chapter); // Extraction par chapitre
    // void stopExtraction();

    // Enregistrement / désenregistrement de directeurs
    void registerDirector(PMTVMedia_MediaDirector* md);
    void unregisterDirector(PMTVMedia_MediaDirector* md);
    void clearDirectorList();
};

#endif

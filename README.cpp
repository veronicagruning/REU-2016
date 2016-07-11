# REU-2016
#include <iostream>
#include <fstream>
using namespace std;
void demoECDReader()

{
    ifstream ecdArchive;
    ecdArchive.open ("123035_IMG.ecd", ifstream::in | ifstream::binary);
    
    short m_version, m_shading, m_mainGain, m_gainBlank, m_adcInput, m_spreadGain, m_absorbGain, m_bfGain, m_txStart, m_txLen, m_numBeams, m_rx1, m_rx2, m_tx1, m_pingFlags, m_tid, m_pid2, m_txSourceLevel;
    double m_txTime, m_endTime, m_txAngle, m_sosAvg, m_vTidalFlow_x, m_vTidalFlow_y;
    int m_halfArr, m_bfFocus, m_modFreq, m_b0, m_b1, m_r0, m_r1, sCount, headerblank, headerType, headerbytes, count, elSz;
    unsigned int mask, m_nRngs, dual, m_nBrgs, m_nBrgs_2, cSize;
    float m_sosAtXd, m_bfAperture, m_txRadius, m_txRng, m_sosAtXd_2, m_fRollFromDMG;
    unsigned char  m_pid, m_txLength, m_scanRate, m_rx1Arr, m_rx2Arr, m_tx1Arr, m_tx2Arr, m_bpp, m_ucStartApertureBeamIndex, m_ucStopApertureBeamIndex, m_ucRollCompensationStatus;
    unsigned short version, version2, Ver, Type, Tag, Tag2, Type2, Ver2, m_softwareGainRamp, m_rangeCompUsed, m_gainType;
    
    char msg[256];
    
    //ecdArchive.read((char*)&version, sizeof(version));
    //ecdArchive.read((char*)&version2, sizeof(version2));
    //ecdArchive.read((char*)&msg, sizeof(msg));
    char c;
    while(true){
        ecdArchive.get(c);
        if(((unsigned char)c) == 0xDE) {
            ecdArchive.get(c);
            if(((unsigned char)c) == 0xDE){
                break;
            }
        }
    }
    while(true){
        ecdArchive.get(c);
        if(((unsigned char)c) == 0xDE) {
            ecdArchive.get(c);
            if(((unsigned char)c) == 0xDE){
                break;
            }
        }
    }
    
    //Type1
    ecdArchive.read((char*)&Type, sizeof(Type));
    ecdArchive.read((char*)&Ver, sizeof(Ver)); //End of Log Header Record
    ecdArchive.read((char*)&m_version, sizeof(m_version)); //From CPing-Version number
    ecdArchive.read((char*)&m_pid, sizeof(m_pid));
    ecdArchive.read((char*)&m_halfArr, sizeof(m_halfArr));
    ecdArchive.read((char*)&m_txLength, sizeof(m_txLength)); //optimum transmit pulse length for a given range
    ecdArchive.read((char*)&m_scanRate, sizeof(m_scanRate));
    ecdArchive.read((char*)&m_sosAtXd, sizeof(m_sosAtXd));
    ecdArchive.read((char*)&m_shading, sizeof(m_shading));
    ecdArchive.read((char*)&m_mainGain, sizeof(m_mainGain));
    ecdArchive.read((char*)&m_gainBlank, sizeof(m_gainBlank));
    ecdArchive.read((char*)&m_adcInput, sizeof(m_adcInput));
    ecdArchive.read((char*)&m_spreadGain, sizeof(m_spreadGain)); //specifies spreading gain
    ecdArchive.read((char*)&m_absorbGain, sizeof(m_absorbGain)); //specifies absorption gain
    ecdArchive.read((char*)&m_bfFocus, sizeof(m_bfFocus));
    ecdArchive.read((char*)&m_bfGain, sizeof(m_bfGain));
    ecdArchive.read((char*)&m_bfAperture, sizeof(m_bfAperture));
    ecdArchive.read((char*)&m_txStart, sizeof(m_txStart));
    ecdArchive.read((char*)&m_txLen, sizeof(m_txLen));
    ecdArchive.read((char*)&m_txRadius, sizeof(m_txRadius));
    ecdArchive.read((char*)&m_txRng, sizeof(m_txRng));
    ecdArchive.read((char*)&m_modFreq, sizeof(m_modFreq)); //the modulation frequency of the sonar in Hz
    ecdArchive.read((char*)&m_numBeams, sizeof(m_numBeams));
    ecdArchive.read((char*)&m_sosAtXd_2, sizeof(m_sosAtXd_2));
    ecdArchive.read((char*)&m_rx1, sizeof(m_rx1));
    ecdArchive.read((char*)&m_rx2, sizeof(m_rx2));
    ecdArchive.read((char*)&m_tx1, sizeof(m_tx1));
    ecdArchive.read((char*)&m_pingFlags, sizeof(m_pingFlags));
    ecdArchive.read((char*)&m_rx1Arr, sizeof(m_rx1Arr));
    ecdArchive.read((char*)&m_rx2Arr, sizeof(m_rx2Arr));
    ecdArchive.read((char*)&m_tx1Arr, sizeof(m_tx1Arr));
    ecdArchive.read((char*)&m_tx2Arr, sizeof(m_tx2Arr)); //End of data from CPing
    ecdArchive.read((char*)&m_tid, sizeof(m_tid)); //From CTgtRec
    ecdArchive.read((char*)&m_pid2, sizeof(m_pid2));
    ecdArchive.read((char*)&m_txTime, sizeof(m_txTime));
    ecdArchive.read((char*)&m_endTime, sizeof(m_endTime));
    ecdArchive.read((char*)&m_txAngle, sizeof(m_txAngle));
    ecdArchive.read((char*)&m_sosAvg, sizeof(m_sosAvg)); //End of data from CTgtRec
    ecdArchive.read((char*)&mask, sizeof(mask)); //From CTgtImg
    ecdArchive.read((char*)&m_bpp, sizeof(m_bpp));
    ecdArchive.read((char*)&m_nRngs, sizeof(m_nRngs));
    ecdArchive.read((char*)&m_b0, sizeof(m_b0));
    ecdArchive.read((char*)&m_b1, sizeof(m_b1));
    ecdArchive.read((char*)&m_r0, sizeof(m_r0));
    ecdArchive.read((char*)&m_r1, sizeof(m_r1));
    ecdArchive.read((char*)&dual, sizeof(dual));
    ecdArchive.read((char*)&m_nBrgs, sizeof(m_nBrgs));
    
    //cData and m_brgTbl arrays are initialised after their size has been read out of the ECD file
    double *m_brgTbl = new double[m_numBeams];
    for (unsigned int i = 0 ; i < m_numBeams ; i++)
    {
        //ecdArchive >> m_brgTbl[i];
        ecdArchive.read((char*)&m_brgTbl[i], sizeof(m_brgTbl[i]));
    }
    
    ecdArchive.read((char*)&m_nBrgs_2, sizeof(m_nBrgs_2));
    ecdArchive.read((char*)&cSize, sizeof(cSize));
    
    unsigned char *cData = new unsigned char[cSize];
    for (unsigned int i= 0; i< cSize; i++)
    {
        //ecdArchive >> cData[i];
        ecdArchive.read((char*)&cData[i], sizeof(cData[i]));
    }
    
    ecdArchive.read((char*)&sCount, sizeof(sCount));
    ecdArchive.read((char*)&Tag, sizeof(Tag));
    
    
    
    //Type2
    ecdArchive.read((char*)&Type2, sizeof(Type2));
    ecdArchive.read((char*)&Ver2, sizeof(Ver2));
    ecdArchive.read((char*)&headerblank, sizeof(headerblank));
    ecdArchive.read((char*)&headerType, sizeof(headerType));
    ecdArchive.read((char*)&headerbytes, sizeof(headerbytes));
    ecdArchive.read((char*)&count, sizeof(count));
    ecdArchive.read((char*)&elSz, sizeof(elSz));
    ecdArchive.read((char*)&m_softwareGainRamp, sizeof(m_softwareGainRamp));
    ecdArchive.read((char*)&m_rangeCompUsed, sizeof(m_rangeCompUsed));
    ecdArchive.read((char*)&m_gainType, sizeof(m_gainType));
    ecdArchive.read((char*)&m_txSourceLevel, sizeof(m_txSourceLevel));
   
    /* ecdArchive.read((char*)&m_ucStartApertureBeamIndex, sizeof(m_ucStartApertureBeamIndex));
    ecdArchive.read((char*)&m_ucStopApertureBeamIndex, sizeof(m_ucStopApertureBeamIndex));
    ecdArchive.read((char*)&m_fRollFromDMG, sizeof(m_fRollFromDMG));
    ecdArchive.read((char*)&m_ucRollCompensationStatus, sizeof(m_ucRollCompensationStatus));
    ecdArchive.read((char*)&m_vTidalFlow_x, sizeof(m_vTidalFlow_x));
    ecdArchive.read((char*)&m_vTidalFlow_y, sizeof(m_vTidalFlow_y)); */
    
    unsigned char *m_pLineX = new unsigned char[2173];
    for (unsigned int i= 0; i< 2173; i++)
    {
        //ecdArchive >> m_pLineX[i];
        ecdArchive.read((char*)&m_pLineX[i], sizeof(m_pLineX[i]));
    }
    
    ecdArchive.read((char*)&Tag2, sizeof(Tag2));
    
    
    ecdArchive.close();
}
int main()
    {
        demoECDReader();
    return 0;
    }

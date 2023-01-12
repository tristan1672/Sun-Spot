/******************************************************************************/
/*!
\par        Project: Alpha Engine
\file       AEAudio.h

\author     Gerald Wong
\date       May 5, 2023

\brief      Audio library that wraps around FMOD

\copyright  Copyright (C) 2023 DigiPen Institute of Technology. Reproduction
			or disclosure of this file or its contents without the prior
			written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#ifndef AE_AUDIO_H
#define AE_AUDIO_H


#include "AEExport.h"
#include "AETypes.h"

typedef struct AEAudio {
	struct FMOD_SOUND* fmod_sound;
} AEAudio;

typedef struct AEAudioGroup {
	struct FMOD_CHANNELGROUP* fmod_group;
} AEAudioGroup;


#ifdef __cplusplus
extern "C"
{
#endif


/******************************************************************************/
/*!
\fn         s32 AEAudioInit (void)

\brief      Initializes the AEAudio module.

\details    Already called in AESysInit, so users shouldn't need to call this.

\retval     s32
            Return 1 if initialization is successful.
            Else return 0.
*/
/******************************************************************************/
AE_API s32 AEAudioInit(void);

/******************************************************************************/
/*!
\fn         void AEAudioUpdate()

\brief      Updates the AEAudio module.

\details    Need to be called somewhere in the user's game loop once per frame.

*/
/******************************************************************************/
AE_API void AEAudioUpdate(void);

/******************************************************************************/
/*!
\fn         s32 AEAudioExit(void)

\brief      Cleans up resources used by the the AEAudio module.

\warning    Already called in AESysExit, so users shouldn't need to call this.

*/
/******************************************************************************/
AE_API void AEAudioExit(void);

/******************************************************************************/
/*!
\fn         s32 AEAudioIsValidAudio(void)

\brief      Checks if the AEAudio given is valid

\retval     s32
      			Returns 0 if invalid, 1 otherwise.
*/
/******************************************************************************/
AE_API s32 AEAudioIsValidAudio(AEAudio audio);

/******************************************************************************/
/*!
\fn         s32 AEAudioIsValidGroup(void)

\brief      Checks if the AEAudioGroup given is valid

\retval     s32
		       	Returns 0 if invalid, 1 otherwise.
*/
/******************************************************************************/
AE_API s32 AEAudioIsValidGroup(AEAudioGroup group);

/******************************************************************************/
/*!
\fn         AEAudioGroup AEAudioCreateGroup(void)

\brief      Create an audio group for audio to be played on.

\retval     AEAudioGroup
            Returns a handle to AEAudioGroup which represents an audio group.
            Use AEAudioIsValidGroup() to check if it's valid.
*/
/******************************************************************************/
AE_API AEAudioGroup AEAudioCreateGroup();

/******************************************************************************/
/*!
\fn         AEAudio AEAudioLoadSound(void)

\brief      Creates an audio that represents a sound to be played. 

\warning    You should use this for short sounds, typically sound effects.

\retval     AEAudio
            Returns a handle to AEAudio which represents an audio that can be played.
            Use AEAudioIsValidAudio() to check if it's valid.
*/
/******************************************************************************/
AE_API AEAudio AEAudioLoadSound(const char* filepath);

/******************************************************************************/
/*!
\fn         AEAudio AEAudioLoadMusic(void)

\brief      Creates an audio that represents a music to be played.

\warning    You should use this for long sounds, typically background music.

\retval     AEAudio
            Returns a handle to AEAudio which represents an audio that can be played.
            Use AEAudioIsValidAudio() to check if it's valid.
*/
/******************************************************************************/
AE_API AEAudio AEAudioLoadMusic(const char* filepath);

/******************************************************************************/
/*!
\fn         void AEAudioPlay(void)

\brief      Plays an audio.

\param      [in] audio
            The audio to play.

\param      [in] group
            The audio group to play the audio on.

\param      [in] volume
            The volume of the audio to play. 
            The range is from 0 to 1, where 0 represents 0% and 1 represents 100%

\param      [in] volume
            The pitch of the audio to play. 
            The range is from 0 to 1, where 0 represents 0% and 1 represents 100%

\param      [in] loops
            The amount of time to loop the audio. 
            0 means that the audio will play once.
            1 means that the audio will play twice.
            -1 means that the audio will loop forever.

*/
/******************************************************************************/
AE_API void AEAudioPlay(AEAudio audio, AEAudioGroup group, float volume, float pitch, s32 loops);

/******************************************************************************/
/*!
\fn         void AEAudioResumeGroup(AEAudioGroup group)

\brief      Resumes the audios in an audio group.

\param      [in] group
            The audio group to resume.

*/
/******************************************************************************/
AE_API void AEAudioResumeGroup(AEAudioGroup group);

/******************************************************************************/
/*!
\fn         void AEAudioStopGroup(AEAudioGroup group)

\brief      Stops the audios in an audio group.

\param      [in] group
            The audio group to stop.

*/
/******************************************************************************/
AE_API void AEAudioStopGroup(AEAudioGroup group);

/******************************************************************************/
/*!
\fn         void AEAudioPauseGroup(AEAudioGroup group)

\brief      Pauses the audios in an audio group.

\param      [in] group
            The audio group to pause.

*/
/******************************************************************************/
AE_API void AEAudioPauseGroup(AEAudioGroup group);

/******************************************************************************/
/*!
\fn         void AEAudioSetGroupVolume(AEAudioGroup group, float volume)

\brief      Changes the volume of the audio group.

\param      [in] group
            The audio group to change the volume of.

\param      [in] volume
            The volume of the audio group. 
            The range is from 0 to 1, where 0 represents 0% and 1 represents 100% 

*/
/******************************************************************************/
AE_API void AEAudioSetGroupVolume(AEAudioGroup group, float volume);

/******************************************************************************/
/*!
\fn         void AEAudioSetGroupPitch(AEAudioGroup group, float pitch)

\brief      Changes the pitch of the audio group.

\param      [in] group
            The audio group to change the pitch of.

\param      [in] pitch
            The pitch of the audio group.
            The range is from 0 to 1, where 0 represents 0% and 1 represents 100%

*/
/******************************************************************************/
AE_API void AEAudioSetGroupPitch(AEAudioGroup group, float pitch);


#ifdef __cplusplus
}
#endif

#endif // AE_AUDIO_H

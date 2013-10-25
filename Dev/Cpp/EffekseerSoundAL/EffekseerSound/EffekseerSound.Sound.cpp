
//----------------------------------------------------------------------------------
// Include
//----------------------------------------------------------------------------------
#include "../EffekseerSoundAL.h"
#include "EffekseerSound.SoundPlayer.h"
#include "EffekseerSound.SoundVoice.h"
#include "EffekseerSound.SoundLoader.h"
#include "EffekseerSound.SoundImplemented.h"

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
namespace EffekseerSound
{

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
Sound* Sound::Create( int32_t numVoices )
{
	SoundImplemented* sound = new SoundImplemented();
	if( sound->Initialize( numVoices ) )
	{
		return sound;
	}
	return NULL;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
SoundImplemented::SoundImplemented()
	: m_mute	( false )
	, m_voiceContainer( NULL )
{
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
SoundImplemented::~SoundImplemented()
{
	StopAllVoices();
	delete m_voiceContainer;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool SoundImplemented::Initialize( int32_t numVoices )
{
	m_voiceContainer = new SoundVoiceContainer( this, numVoices );
	
	return true;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void SoundImplemented::SetListener( const ::Effekseer::Vector3D& pos, 
		const ::Effekseer::Vector3D& at, const ::Effekseer::Vector3D& up )
{
	::Effekseer::Vector3D front;
	::Effekseer::Vector3D::Normal(front, at - pos);
	float orientation[3 * 2];
	orientation[0] = front.X;
	orientation[1] = front.Y;
	orientation[2] = front.Z;
	orientation[3] = up.X;
	orientation[4] = up.Y;
	orientation[5] = up.Z;

	alListenerfv(AL_POSITION, &pos.X);
	alListenerfv(AL_ORIENTATION, orientation);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void SoundImplemented::Destory()
{
	delete this;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
::Effekseer::SoundPlayer* SoundImplemented::CreateSoundPlayer()
{
	return new SoundPlayer(this);
}
	
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
::Effekseer::SoundLoader* SoundImplemented::CreateSoundLoader( ::Effekseer::FileInterface* fileInterface )
{
	return new SoundLoader( fileInterface );
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void SoundImplemented::StopAllVoices()
{
	m_voiceContainer->StopAll();
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void SoundImplemented::SetMute( bool mute )
{
	m_mute = mute;
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
SoundVoice* SoundImplemented::GetVoice()
{
	return m_voiceContainer->GetVoice();
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void SoundImplemented::StopTag( ::Effekseer::SoundTag tag )
{
	m_voiceContainer->StopTag(tag);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
void SoundImplemented::PauseTag( ::Effekseer::SoundTag tag, bool pause )
{
	m_voiceContainer->PauseTag(tag, pause);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
bool SoundImplemented::CheckPlayingTag( ::Effekseer::SoundTag tag )
{
	return m_voiceContainer->CheckPlayingTag(tag);
}

//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------
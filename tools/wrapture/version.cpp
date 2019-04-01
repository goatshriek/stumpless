#include <stumpless/version.h>

namespace stumpless {
  class Version {
    private:
      struct stumpless_version version;

    public:
      Version( int major, int minor, int patch );
      Version( struct stumpless_version version );
      Version( const struct stumpless_version *version );
      static Version GetCurrent( void );
      int GetMajor( void ) const;
      int GetMinor( void ) const;
      int GetPatch( void ) const;
  };

  Version::Version( int major, int minor, int patch ) {
    this->version.major = major;
    this->version.minor = minor;
    this->version.patch = patch;
  }

  Version::Version( struct stumpless_version version ) {
    this->version.major = version.major;
    this->version.minor = version.minor;
    this->version.patch = version.patch;
  }

  Version::Version( const struct stumpless_version *version ) {
    this->version.major = version->major;
    this->version.minor = version->minor;
    this->version.patch = version->patch;
  }

  static Version Version::GetCurrent( void ) {
    return Version( stumpless_get_version(  ) );
  }

  int Version::GetMajor( void ) {
    return this->version.major;
  }

  int Version::GetMinor( void ) {
    return this->version.minor;
  }

  int Version::GetPatch( void ) {
    return this->version.patch;
  }
}

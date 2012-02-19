#ifndef XTITAN_UTILITIES_SETTING_HPP
#define XTITAN_UTILITIES_SETTING_HPP

#include "xTitan/Utility/Config.hpp"

#include <QtCore/QString>
#include <QtCore/QVariant>

#include <memory>

namespace xtitan {
	namespace utilities {

		class XTITAN_CORE_DLL Setting {
		public:
			static Setting & getInstance();

			QVariant get( const QString & key ) const;
			void set( const QString & key, const QVariant & value );

			void save() const;

			void setFilePath( const QString & path );

		private:
			class Private;

			Setting();
			~Setting();

			std::shared_ptr< Private > p_;
		};

	}
}

#endif

Name:           persistence-client-library
Version:        0.9.0
Release:        0
Summary:        GENIVI Persistence Client Library
License:	MPL-2.0
Group:		Automotive/GENIVI
Url:            http://projects.genivi.org/persistence-client-library/
Source0:        %name-%version.tar.xz
Source1001: 	persistence-client-library.manifest
BuildRequires:	autoconf >= 2.64, automake >= 1.11
BuildRequires:  libtool >= 2.2
BuildRequires:  pkgconfig
BuildRequires:	pkgconfig(automotive-dlt)
BuildRequires:	pkgconfig(dbus-1)
BuildRequires:	pkgconfig(libperscommon)

%description
The Persistence Management is responsible to handle persistent data,
including all data read and modified often during a lifetime of an
infotainment system. "Persistent data" is data stored in a
non-volatile storage such as a hard disk drive or FLASH memory.

%package devel
Summary:  Development files for package %{name}
Group:    Automotive/GENIVI
Requires: %{name} = %{version}

%description devel
This package provides header files and other developer releated files
for package %{name}.

%prep
%setup -q
cp %{SOURCE1001} .

%build
autoreconf --install
%configure --disable-static

make %{?_smp_mflags}

%install
%make_install

%post   -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%manifest %{name}.manifest
%defattr(-,root,root)
%license COPYING
%{_libdir}/libpersistence_client_library.so.*
%config %{_sysconfdir}/pclCustomLibConfigFile.cfg

%files devel
%manifest %{name}.manifest
%{_includedir}/*.h
%{_libdir}/libpersistence_client_library.so
%{_libdir}/pkgconfig/persistence_client_library.pc

%changelog

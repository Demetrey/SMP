# SMP

***Simple Media (Music) Player***

**Описание**

Данный плеер представляет собой бесплатное, свободное от рекламы решение с открытым исходным кодом, направленное на воспроизведение аудио на платформах MS Windows, Linux/X11, Android. Разрабатывается на чистом энтузиазме без какой-либо поддержки. 

**Форматы аудио**:

 AIFF, APE, ALAC, FLAC, XM, IT, S3M, MOD, UMX, FLAC, MIDI, OPUS

**Description**

This player is a free, ad-free and open source audio playback solution for MS Windows, Linux/X11, Android platforms. Developed on pure enthusiasm without any support.

**Audio Formats**:

AIFF, APE, ALAC, FLAC, XM, IT, S3M, MOD, UMX, FLAC, MIDI, OPUS

**Screenshots/Внешний вид**

MS Windows / Linux:

<img title="" src="file:///D:/gits/SMP_code/SMP/Screenshots/WinLin1.png" alt="Интерфейс приложения для MS Windows и Linux" data-align="center" width="300">

<img title="" src="file:///D:/gits/SMP_code/SMP/Screenshots/WinLin2.png" alt="Интерфейс на Windows/Linux" data-align="center" width="300">

<img title="" src="file:///D:/gits/SMP_code/SMP/Screenshots/Android1.jpg" alt="Интерфейс Android" data-align="center" width="145">

<img title="" src="file:///D:/gits/SMP_code/SMP/Screenshots/Android2.jpg" alt="Интерфейс Android" data-align="center" width="145">

**Описание решения**

Аудиоплеер с набором основных функций:

- воспроизведение аудиофайлов;

- потоковое воспроизведение и воспроизведение по URL (протоколы HTTP/HTTPS/FTP);

- основные функции управления воспроизведением;

- эквалайзер;

- визуализация звука;

- составление плейлистов;

- управление текущей очередью воспроизведения;

- медиауведомления на Android;

- работа с аудио фокусом на Android;

- две стандартные цветовые схемы оформления: светлая и темная;

- поддержка двух языков: русского и английского.

Планируется:

- синхронизация медиатеки по локальной сети (дополнительно).

**Поддерживаемые платформы**

- Windows (7, 8, 8.1, 10);

- Linux;

- Android (6+).

**Реализация**

Qt 5 (5.15.2)

Пользовательский интерфейс: QML

Используемые дополнительные библиотеки:

- [Bass Audio Library](http://www.un4seen.com/);

- [TagLib](https://taglib.org/).

[Bass AL](http://www.un4seen.com/) обладает всем необходимым для реализации заявленного набора функций воспроизведения, а также дополнительными плагинами, расширяющими возможности данной библиотеки.

[TagLib](https://taglib.org/) позволяет получить доступ к тегам аудиофайлов, в том числе обложкам.

**Description of the solution**

Audio player with a set of basic functions:

- playback of audio files;

- streaming playback and playback by URL (HTTP/HTTPS/FTP protocols);

- basic playback control functions;

- equalizer;

- sound visualization;

- compilation of playlists;

- management of the current playback queue;

- media notifications on Android;

- work with audio focus on Android;

- two standard color schemes: light and dark;

- support for two languages: Russian and English.

Planned:

- synchronization of the media library over the local network (optional).

**Supported Platforms**

- Windows (7, 8, 8.1, 10);

- Linux;

- Android (6+).

**Implementation**

Qt 5 (5.15.2)

User interface: QML

Additional libraries used:

- [Bass Audio Library](http://www.un4seen.com/);

- [TagLib](https://taglib.org/).

[Bass AL](http://www.un4seen.com/) has everything necessary to implement the declared set of playback functions, as well as additional plugins that expand the capabilities of this library.

[TagLib](https://taglib.org/) allows you to access audio file tags, including cover art.
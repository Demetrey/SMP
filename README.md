# SMP

***Simple Media (Music) Player***



**Description of the planned solution**

Audio player with a set of basic functions:

- playback of audio files;

- URL streaming (HTTP/HTTPS/FTP protocols);

- basic playback controls;

- equalizer;

- visualization;

- compiling playlists;

- managing the current playback queue;

- sync library over LAN (optional).

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



**Описание планируемого решения**

Аудиоплеер с набором основных функций:

- воспроизведение аудиофайлов;

- потоковое воспроизведение по URL (протоколы HTTP/HTTPS/FTP);

- основные функции управления воспроизведением;

- эквалайзер;

- визуализация;

- составление плейлистов;

- управление текущей очередью воспроизведения;

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
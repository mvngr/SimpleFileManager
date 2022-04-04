# SimpleFileManager

Пример простого файлового менеджера, реализованного на Qt с использованием QML

## Сборка deb пакета

Для того, чтобы собрать deb пакет на основе текущего кода достаточно выполнить:

    cmake -S /path/to/SimpleFileManager/ -B /path/to/build/dir
    make package
  
После чего у вас появиться пакет `SimpleFileManager-1.0.1.deb`

# chess2d_test

### Общая информация
Тестовое задание по написанию простых 2d шахмат на движке oxygine.
Реализован минимальный функционал, без учета шаха, мата, рокировки и т.д.
Инструкция для запуска под linux (ubuntu)

### Установка необходимых пакетов
```
sudo apt install git build-essential libz-dev libsdl2-dev libpng-dev libjpeg-dev
```

### Скачиваем Oxygine
Сначала создадим папку куда будем скачивать
```
mkdir ~/oxygine
cd ~/oxygine
```
Дальше качаем репозиторий 
```
git clone https://github.com/oxygine/oxygine-framework.git
```

### Скачиваем и запускаем шахматы
В той же папке `~/oxygine` качаем репозиторий игры
```
git clone https://github.com/quadro9/chess2d_test.git
```
Заходим внутрь папки с игрой
```
cd chess2d_test
```
И запускаем игру
```
./run.sh
```

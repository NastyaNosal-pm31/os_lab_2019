#!/bin/bash
echo 'Текущее местоположение'
pwd
echo 'Текущие дата и время'
date +%D
date +%S:%M:%H
echo 'Содержимое переменной окружения PATH':$PATH 
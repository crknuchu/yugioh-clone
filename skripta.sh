#!/usr/bin/bash
x=`git log -1 --format=%s |  wc -m`

if [[ $x -ge 15 ]]; then
       echo "Commit poruka je prevelika, probaj da napises u manje reci"
       exit 1
fi
echo "Duzina commit poruke je odgovarajuca!"
exit 0

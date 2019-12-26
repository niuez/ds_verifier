for FILE in `git ls-files`; do
  TIME=`git log --pretty=format:%ci -n1 $FILE`
  STAMP=`date -d "$TIME" +"%y%m%d%H%M.%S"`
  echo $TIME'\t'$FILE'\t'$STAMP
  touch -t $STAMP $FILE
done

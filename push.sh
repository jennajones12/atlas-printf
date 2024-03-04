touch push.sh
chmod +x push.sh
vi push.sh

#!/bin/bash

echo "Enter Commit Message"
read message

git add .
git commit -m $message
git push

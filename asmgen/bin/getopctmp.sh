#!/usr/bin/env bash

# cat $1 | \
#     awk -F\| '{printf ("%s|%s|%s\n",                                         \
#                      gensub("  *", "", "g", gensub("0x", "", "g", $1)),    \
#                        gensub("[#;][#;]*", "", "g", $3),                     \
#                        $2)}                             '                | \
#     sort                                                                   | \
#     uniq

cat $1 | \
    awk -F\| '{printf ("%s|%s|%s\n",                          \
                       gensub ("0x", "", "g", $1),            \
                       gensub ("[#;][#;]*", "", "g", $3),     \
                       $2)}                               ' | \
    sed -e "s/ | /|/g"                                | \
    sort                                                    | \
    uniq

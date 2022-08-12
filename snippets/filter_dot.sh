is_good=1
while IFS= read -r line; do
    if [[ ( "$line" == *"cluster_std"* ) || ( "$line" == *"cluster___gnu_cxx"* ) ]]; then
        is_good=0
    fi
    if [[ $is_good == 1 ]]; then
        echo "$line"
    else
        echo "# $line"
    fi
    if [[ "$line" == "}" ]]; then
        is_good=1
    fi
done


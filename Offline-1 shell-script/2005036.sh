#!/bin/bash

csv_file="marks.csv"
issues_folder="issues"
checked_folder="checked"
temp_dir="temp"


allowed_archive_inputs=("true" "false")
allowed_archive_formats=("zip" "rar" "tar")
allowed_languages=("c" "cpp" "python" "sh")


present_in_array() {
    local input=$1
    local -n array=$2
    local matched=0

    for value in ${array[@]}
    do
        if [ "$input" = "$value" ]
        then
            matched=1
            break
        fi
    done
    
    echo $matched
}

veify_array_elements() {
    local -n allowed_elements=$1
    shift
    local  array=("$@") 

    local valid=1

    for element in "${array[@]}" 
    do
        local present=$(present_in_array "$element" allowed_elements)
        if [[ $present = 0 ]]
        then
            valid=0
            break
        fi
    done

    echo $valid
}

is_number() {
    local input=$1

    if [[ "$input" =~ ^[0-9]+$ ]]
    then
        echo 1 
    else
        echo 0
    fi
}

numbers_in_order() {
    local num1=$1
    local num2=$2

    if [ $2 -gt $num1 ]
    then
        echo 1
    else
        echo 0
    fi
}

read_input() {
    line_no=0
    input_file_error=0

    while IFS= read -r line
    do
        line_no=$(($line_no + 1))

        case $line_no in
            1) archived="$line"

                verify=$(present_in_array "$archived" allowed_archive_inputs)
                
                if [ $verify = 0 ]
                then
                    echo "error in line 1 : possible inputs true, false"
                    input_file_error=1
                fi
                ;;
                

            2) used_archives="$line"
               
                verify=$(veify_array_elements allowed_archive_formats ${used_archives[@]})

                if [ $verify = 0 ]
                then
                    echo "error in line 2 : allowed archive types ${allowed_archive_formats[@]}"
                    input_file_error=1
                fi

                ;;

            3) used_languages="$line"
               
                verify=$(veify_array_elements allowed_languages ${used_languages[@]})

                if [ $verify = 0 ]
                then
                    echo "error in line 3 : allowed languages ${allowed_languages[@]}"
                    input_file_error=1
                fi
                ;;

            4) full_mark="$line"
               
                if [ $(is_number "$full_mark") = 0 ]
                then
                    echo "error in line 4 : total mark must be a number" 
                    input_file_error=1
                fi
                ;;

            5) unmatched_panalty="$line"
              
                if [ $(is_number "$unmatched_panalty") = 0 ]
                then
                    echo "error in line 5 : mismatch penalty must be a number" 
                    input_file_error=1
                fi
                ;;

            6) submission_dir=""$(pwd)"/"$line""
                echo $submission_dir;;

            7) IFS=" " read -ra id_range <<< "$line"
               
                student_id_min=${id_range[0]}
                student_id_max=${id_range[1]}
                
                if [ $(is_number "$student_id_min") = 0 ] || [ $(is_number "$student_id_max") = 0 ]
                then
                    echo "error in line 7 : invalid student ids" 
                    input_file_error=1
                fi
                ;;
            
            8) expected_out_file=""$(pwd)"/"$line""
                ;;
               
            9) submission_panalty="$line"

                if [ $(is_number "$submission_panalty") = 0 ]
                then
                    echo "error in line 9 : submission panalty must be a number" 
                    input_file_error=1
                fi
                ;;
            
            10) plagiarism_file=""$(pwd)"/"$line""
                ;;
              
            11) plagiarism_Penalty="$line"
            
                if [ $(is_number "$plagiarism_Penalty") = 0 ]
                then
                    echo "error in line 11 : plagiarism penalty must be a number" 
                    input_file_error=1
                else
                    plagiarism_Penalty=$(($plagiarism_Penalty / 100))
                fi

                ;;
        esac

    done < "$input_file"


    if [ $input_file_error = 1 ]
    then
        echo "------------exiting execution-------------"
        exit
    fi
}

check_id_range() {
    local id=$1

    if [ $id -ge $student_id_min ] && [ $id -le $student_id_max ] 
    then
        echo 1
    else
        echo 0
    fi
}

check_plagiarism() {
    local student_id=$1
   
    while IFS= read -r line 
    do
        if [ $line = $student_id ]
        then
            submission_issues+=("plagiarism detected ")
            net_mark="-$(($full_mark * $plagiarism_Penalty))"

            return
        fi

    done < "$plagiarism_file"

    net_mark=$(($obtained_marks - $deducted_marks))
}

compare_file() {
    local output_file=$1
    local line_no=0
    local mismatch=0

    while IFS= read -r line 
    do
        line_no=$(($line_no + 1))
        
        local matched_lines=$(grep -Fxn "$line" "$output_file" | cut -d: -f1)
        local match_found=0

        for l in $matched_lines
        do
            if [ $line_no -eq $l ]
            then
                match_found=1
                break
            fi
        done
        
        if [ $match_found = 0 ]
        then
            mismatch=$(($mismatch + 1))
        fi
        
    done < "$expected_out_file"

    echo $mismatch
}

valid_language() {
    local extension="$1"
    local matched=0

    if [ $extension = "py" ]
    then
        extension="python"
    fi

    echo $(present_in_array "$extension" used_languages)
}

run() {
   
    local full_name=$1
    local output_file=$2

    local file_extension=${full_name##*.}
    
    touch "$output_file"

    case $file_extension in
        c|cpp) g++ $full_name
               ./a.out > "$output_file"
               rm ./a.out;;

        py) python3 $full_name > "$output_file";;

        sh) bash $full_name > "$output_file";;
    esac

}

process_file() {
    local folder_name=$1

    local full_name=$(ls "$folder_name")
    local file_name=${full_name%.*}
    local file_extension=${full_name##*.}

    # if file not named as student id
    if [ "$folder_name" != "$file_name" ]
    then
        submission_issues+=("issue case #4 ")
    fi

    if [ $(valid_language "$file_extension") = 0 ]
    then
        submission_issues+=("issue case #3 ")
        mv "$folder_name" "$issues_folder"
    else

        cd "$folder_name"

        output_file=$(echo ${folder_name}_output.txt)

        run "$full_name" "$output_file"
        
        mismatch=$(compare_file "$output_file")

        obtained_marks=$(($full_mark - ($mismatch * $unmatched_panalty)))
        
        cd ..

        mv "$folder_name" "$checked_folder"
    fi

    
}

write_to_csv() {
    echo "$file_name,$obtained_marks,$deducted_marks,$net_mark,${submission_issues[*]}" >> "$csv_file"
}

handle_non_archived_file() {
    mkdir "$file_name"
    mv "$file" "$file_name"

    return 0
}

handle_archived_file() {

    # valid archived format
    if [ -f $file ] && [ $(present_in_array $file_extension used_archives) = 0 ]
    then
        submission_issues+=("issue case #2 ")
        
        return 1
    fi

    # submitted directory
    if [ -d "$file" ]
    then
        submission_issues+=("issue case #1 ")
    else
        # extract in temp directory
        case $file_extension in
            zip)  unzip -q "$file" -d "$temp_dir";;
                    
            rar)  unrar x  -inul "$file" "$temp_dir";;
                    
            tar)  tar xf "$file" -C "$temp_dir";;
        esac

        extracted_folder=$(ls $temp_dir)

        if [ "$extracted_folder" != "$file_name" ]
        then
            submission_issues+=("issue case #4 ")
            # rename extraced folder as the zip file name
            mv "$temp_dir/$extracted_folder" "$temp_dir/$file_name"
        fi

        mv "$temp_dir/$file_name" .
    fi
    return 0
}


# ----------------------------------------------------------------------------------

input_file="$1"

read_input

cd "$submission_dir"

touch "$csv_file"
echo "id,marks,marks_deducted,total_marks,remarks" >> "$csv_file"

mkdir $issues_folder
mkdir $checked_folder
mkdir $temp_dir

for file in $(ls | sort)
do
    submission_issues=()
    obtained_marks=0
    deducted_marks=0
    net_mark=0

    file_extension=${file##*.}
    file_name=${file%.*}

    # if file name not a number
    if [[ ! "$file_name" =~ ^[0-9]+$ ]]
    then
        continue
    fi

    if [ $archived = "false" ]
    then
        handle_non_archived_file
    else
        handle_archived_file
    fi

    # if folder created/unzipped successful
    if [ $? = 0 ]
    then
        # not in student range
        if [ $(check_id_range $file_name) = 0 ]
        then
            submission_issues+=("issue case #5 ")
            mv "$file_name" "$issues_folder"
        else
            process_file "$file_name"
        fi

    fi

    deducted_marks=$(($submission_panalty * ${#submission_issues[@]}))
    check_plagiarism $file_name
    
    write_to_csv
    
done

rm -r $temp_dir

# -----------------------------------------------------------------------------------

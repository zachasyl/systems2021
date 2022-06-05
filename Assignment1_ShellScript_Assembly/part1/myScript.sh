#!/bin/bash
# The line above makes your script executable.
# You should write your tutorial in here.
# Include comments inline with your script explaining what is going on.

# You might start out by first saying the purpose of the script and
# demonstrating its usage.


# The purpose of this script is to randomly find a top 100 movie to watch in a category of your choosing. 
# After you choose a category, the script randomly displays a movie from that category. If you really dont want to watch that one, you
# can keep selecting.

# How it Works (Generally):
# The script downloads a page from rottentomatoes.com depending on the category you choose and creates a new html file.
# Then the script reads through the file such that it only echos lines that contain movies and it parses the movie displaying only title and year.
# The user may keep selecting different categories and if the appropriate url is already downloaded, it will not be downloaded again.
# One the user selects to exit, the file will be deleted.
#---------------------------------------------------------------------------------


# random variable is a line 1 through 100.
# start is the line containing the first movie. 
# skip is the amount of lines separating each move.
# Note that if RT changes the skip and start would need to be updated and this script depends on the skip being even and also the same in ea# each category.

randomize(){

        random=$((1 + RANDOM % 100))
        i=0
	# note that this line seems to vary it was 1240 a few days ago RT the skip is always 14 but the start may need to be adjusted
	# Note: I've used a late to update/simplify the program and now it doesnt directly get the data from RT but instead
	# gets it from files I've provided along with the script.
        start=1269
        skip=14
        movie=$((start + random*skip))

	#IFS determines how word splitting will proceed.
	# script will read every line and if iterator i current line is equal to a movie line itll echo the line and cut
	# anything after the '<' symbol (this avoids displaying html tags).
        while IFS= read -r line
	# I could not get an if then statement to work within the while or do command....
	# but what this does is test if i = $movie each line and if it does itll print the line with appropriate cuts
	# normally this would be used to test if a condition is true and if it is echo "true"
	# https://bash.cyberciti.biz/guide/Test_command
		# while commands; do commands; done 
		# https://www.geeksforgeeks.org/while-command-in-linux-with-example/
       		do
		test $((++i)) = $movie &&  
	        echo "$line" | cut -d '<' -f 1 


        	done < "$input" 	
		
}


# The select menu screen concept came from the following url:
# https://askubuntu.com/questions/1705/how-can-i-create-a-select-menu-in-a-shell-script

# The value of this variable is used as the prompt for the select command. 
PS3='What category of movie do you want to watch?: '
options=("Comedy" "Horror" "Drama" "Quit" "Delete")

select opt in "${options[@]}"
do
    case $opt in
        "Comedy")
		input="rottenRandomComedy.html"
		# displays opt you chose of options
            	echo "you chose $opt"
		# if there is not a file in existene with name of input. this is no longer needed since i've provided the files. the point was tht it would not redownload the file from rottentomatoes if you already downloaded it once.
            	if [ ! -e "$input" ]
                then
            	wget -O rottenRandomComedy.html  # this used to wget from https://www.rottentomatoes.com/top/bestofrt/top_100_comedy_movies/...however, the start line for the movies seems to change by a small random amount each day or something?
            	fi # fi signals end of it statement.
            	randomize
	    
            ;;
        "Horror")
		input="rottenRandomHorror.html"
		echo "you chose $opt"
		if [ ! -e "$input" ]
                then
                wget -O rottenRandomHorror.html
		fi
                randomize
            ;;
        "Drama")
		input="rottenRandomDrama.html"
		echo "you chose $opt"
		if [ ! -e "$input" ]
                then	
            	echo "you chose choice $opt"
            	wget -O rottenRandomDrama.html 
	    	fi
            	randomize

            ;;
        "Quit")
		# originally the program deleted the file upon quitting but delete is serparate.
		# originally it made sense to delete on quit since wget would redowload from RT.com
		#breaks away from options menu    
            	break
            	;;

	"Delete")
                # deletes file before exit, stops selection with break. only if it exists. Potentially deletes 3 files with 1 button.
                if [ -e "rottenRandomComedy.html" ]
                then
                rm rottenRandomComedy.html
                fi

                if [ -e "rottenRandomHorror.html" ]
                then
               rm rottenRandomHorror.html
                fi

                if [ -e "rottenRandomDrama.html" ]
                then
                rm rottenRandomDrama.html
                fi
                break
                ;;
                                                                                                                           *) echo "invalid option $REPLY";;



    esac
done
             

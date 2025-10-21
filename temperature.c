//temperature.c

#include <stdio.h>
#include <stdbool.h>


float farenheit_to_celcius(float temperature){
    float new_temperature;  //initalize temperature
    new_temperature = (temperature - 32.0) * (5.0/9.0); //convert farenheit_to_celcius
    return new_temperature; //return the new temperature
}

//this is the same the entire way down, just to different temperatures

float celcius_to_farenheit(float temperature){
    float new_temperature;
    new_temperature = (temperature * (9.0/5.0)) + 32.0;
    return new_temperature;
}

float farenheit_to_kelvin(float temperature){
    float new_temperature;
    new_temperature = (temperature - 32.0) * (5.0/9.0) + 273.15;
    return new_temperature;
}

float kelvin_to_farenheit(float temperature){
    float new_temperature;
    new_temperature = (temperature - 273.15) * (9.0/5.0) + 32.0;
    return new_temperature;
}

float celcius_to_kelvin(float temperature){
    float new_temperature;
    new_temperature = temperature + 273.15;
    return new_temperature;
}

float kelvin_to_celcius(float temperature){
    float new_temperature;
    new_temperature = temperature - 273.15;
    return new_temperature;
}


float convert_temperature_to_another(float original_temperature, char original_unit, char converting_to_unit){
    float new_temperature; //initalize new temperature
    
    if (original_unit == 'C'){
        //starting unit Celcius
        if (converting_to_unit == 'F'){
            //convert C to Farenheit
            new_temperature = celcius_to_farenheit(original_temperature);
        }else if (converting_to_unit == 'K'){
            //convert C to Kelvin
            new_temperature = celcius_to_kelvin(original_temperature);
        }
    }else if (original_unit == 'F'){   
        //starting unit Farenheit
        if (converting_to_unit == 'C'){
            //convert F to Celcius
            new_temperature = farenheit_to_celcius(original_temperature);
        } else if (converting_to_unit == 'K'){
            //convert F to Kelvin
            new_temperature = farenheit_to_kelvin(original_temperature);
        }

    }else if (original_unit == 'K'){
        //starting unit Kelvin
        if (converting_to_unit == 'F'){
            //convert F to Farenheit
            new_temperature = kelvin_to_farenheit(original_temperature);
        }else if (converting_to_unit == 'C'){
            //convert F to Celcius
            new_temperature = kelvin_to_celcius(original_temperature);
        }
    }       

    return new_temperature; //return the new temperature

}

float get_temperature_number_from_user(){
    float usr_temperature; //get numeric starting temperature value
    printf("What's your temperature?: "); //print to the user asking for that value
    scanf("%f", &usr_temperature); //get the value from the user
    return usr_temperature;    //return the given user temperature
}

char get_temperature_unit_from_user(bool is_conversion, char original_unit){
    char usr_character;
    bool is_valid_character = false;

    while (is_valid_character == false){
        scanf(" %c", &usr_character); //get input from user
        if (usr_character == 'C' || usr_character == 'F' || usr_character == 'K'){ //if the input is valid
            if (is_conversion == true && original_unit == usr_character){   
                //the given unit was the same as the previous one
                //can't happen when converting units
                printf("Cannot give same input twice. Try again:");
            }else{  //valid input was given
                is_valid_character = true;
            }
        }else{
            //invalid input given
            printf("Invalid input given. Try again:");
        }
    }

    return usr_character;   //return the user character

}

void weather_fact(float temperature){
    printf("\n");
    if (temperature < 0){   // temp < 0
        printf("Temperature category: Freezing");
        printf("\nWeather advisory: Good day for some snow. Wear a coat or you'll get frost bite.");
    }else if (0 <= temperature && temperature < 10){     //0 <= temp < 10
        printf("Temperature category: Cold");
        printf("\nWeather advisory: It'd be warm if it were this temperature in the winter. Wear a coat or something like that");
    }else if (10 <= temperature && temperature < 25){   //10 <= temp < 25
        printf("Temperature category: Comfortable");
        printf("\nWeather advisory: Great day for football. Jacket weather.");
    }else if (25 <= temperature && temperature < 35){ //25 <= temp < 35
        printf("Temperature category: Hot");
        printf("\nWeather advisory: No jacket needed! It's a great day outside. Don't forget to drink some water!");
    }else{  // 35 <= temp
        printf("Temperature category: Extreme Heat");
        printf("\nWeather advisory: Either this is really hot or the surface temperature of the sun. Best advice is to put on some sun screen.");
    }
    return; //get out of the function
}

int main(){
    float usr_temp; //get numeric starting temperature value
    usr_temp = get_temperature_number_from_user();

    char usr_unit;  //get the starting temperature unit
    printf("What unit are you using (Use first letter only, C, F, K): ");    //print to the user to get that unit
    usr_unit = get_temperature_unit_from_user(false, 'X');  //get the unit from the user
    //the false is because we aren't converting to a temperature
    //the 'X' is to give a junk char; we aren't converting to a temperature

    char usr_convert_unit;  //get the conversion temperature unit
    printf("What unit are you converting to?: ");
    usr_convert_unit = get_temperature_unit_from_user(true, usr_unit);  //get the unit from the user

    float new_temperature = convert_temperature_to_another(usr_temp, usr_unit, usr_convert_unit);
    printf("\nConverted temperature: %f %c", new_temperature, usr_convert_unit);

    float celcius_temperature; //get the celcius temp for temperature category

    if (usr_unit == 'C'){   //we were given celcius to begin with
        celcius_temperature = usr_temp;    //get the original temperature
    } else if (usr_convert_unit == 'C'){    //we converted to celcius already
        celcius_temperature = new_temperature; //get the new temperature
    }else{
        celcius_temperature = convert_temperature_to_another(usr_temp, usr_unit, 'C');
        //create a new conversion of the original temp to celcius
        //put it to celcius temperature.
    }
    weather_fact(celcius_temperature);  //get the weather fact with the celcius temperature

    return 0;
}

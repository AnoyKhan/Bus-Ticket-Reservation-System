#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define ACCOUNT_FILE "accounts.txt"
#define TICKET_FILE "tickets.txt"
#define MAX_TICKETS 30

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

const char *bus_times[] = {"06:00 AM", "12:00 PM", "06:00 PM"};
const char *locations[] = {"Dhaka", "Barishal", "Chittagong", "Faridpur", "Kurigram"};
#define TOTAL_TIMES 3
#define TOTAL_LOCATIONS 5

typedef struct {
    char F_name[50];
    char L_name[50];
    char address[100];
    char phn[12];
    int pin;
} Account;

typedef struct {
    char phn[12];
    char from[30];
    char to[30];
    char time[15];
    int seatNo;
    int price;
    char trip_id[10]; // Format: TRIP0001, TRIP0002, etc.
} Ticket;

// Improved input handling for strings
void safe_string_input(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
    }
}

// Improved file operations
FILE* safe_file_open(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (!file) {
        fprintf(stderr, "Error opening file %s: %s\n", filename, strerror(errno));
        return NULL;
    }
    return file;
}

// Improved input validation
int validate_selection(int choice, int min, int max) {
    if (choice < min || choice > max) {
        printf("Invalid selection. Please choose between %d and %d\n", min, max);
        return 0;
    }
    return 1;
}

void pin_check(int *a, int *b);
void save_account(Account acc);
int verify_account(const char *phn, int pin);
int phone_valid(const char *phn);
void generate_trip_id(char *trip_id);
void book_ticket(const char *phn);
void view_tickets(const char *phn);
void cancel_ticket(const char *phn);
void admin_panel();
void sign_in();
void sign_up();
void menu();

// String trimming helper function to clean inputs
void str_trim(char *str) {
    if (!str) return;
    
    // Trim leading whitespace
    char *start = str;
    while (isspace(*start)) start++;
    
    // If the string is all whitespace
    if (*start == '\0') {
        *str = '\0';
        return;
    }
    
    // Shift the string to remove leading whitespace
    if (start != str) {
        char *dest = str;
        while (*start) *dest++ = *start++;
        *dest = '\0';
    }
    
    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && (isspace(*end) || *end == '\r' || *end == '\n')) {
        *end = '\0';
        end--;
    }
}

int phone_valid(const char *phn) {
    // Check if the length is exactly 11
    if (strlen(phn) != 11) {
        return 0;
    }

    // Check if all characters are digits
    for (int i = 0; i < 11; i++) {
        if (!isdigit(phn[i])) {
            return 0;  // Invalid if a non-digit character is found
        }
    }

    return 1;  // Valid phone number
}
void generate_trip_id(char *trip_id) {
    FILE *file = fopen(TICKET_FILE, "r");
    Ticket temp;
    int max_id = 0;

    if (file) {
        char time1[10], time2[5];

        while (fscanf(file, "%s %s %s %s %s %d %s %d",
                      temp.phn, temp.from, temp.to,
                      time1, time2, &temp.seatNo, temp.trip_id, &temp.price) == 8) {

            // join time1 + time2 -> temp.time (optional)
            snprintf(temp.time, sizeof(temp.time), "%s %s", time1, time2);

            if (strncmp(temp.trip_id, "TRIP", 4) == 0) {
                int id_num = atoi(temp.trip_id + 4); // e.g. 0001 → 1
                if (id_num > max_id) {
                    max_id = id_num;
                }
            }
                      }
        fclose(file);
    }

    sprintf(trip_id, "TRIP%04d", max_id + 1); // TRIP0002, TRIP0003 ...
}


void pin_check(int *a, int *b) {
    while (*a != *b) {
        printf(RED "\nYour pin doesn't match! Please try again!\n" RESET);
        printf("Enter new PIN: ");
        scanf("%d", a);
        printf("Confirm new PIN: ");
        scanf("%d", b);
    }
    printf(GREEN "\nAccount successfully created!\n" RESET);
}

void save_account(Account acc) {
    FILE *file = fopen(ACCOUNT_FILE, "a");
    if (file) {
        fprintf(file, "%s %s %s %s %d\n", acc.F_name, acc.L_name, acc.address, acc.phn, acc.pin);
        fclose(file);
    }
}

int verify_account(const char *phn, int pin) {
    FILE *file = fopen(ACCOUNT_FILE, "r");
    Account acc;
    if (file) {
        while (fscanf(file, "%s %s %s %s %d", acc.F_name, acc.L_name, acc.address, acc.phn, &acc.pin) != EOF) {
            if (strcmp(acc.phn, phn) == 0) {
                while (pin != acc.pin) {
                    printf(RED "Your PIN doesn't match! Please try again: " RESET);
                    scanf("%d", &pin);
                }
                fclose(file);
                return 1;
            }
        }
        fclose(file);
    }
    return 0;
}

void sign_in() {
    char phn[12];
    int pin;
    while (1) {
        printf(CYAN "\n#### Welcome to Sign In Section ####\n" RESET);
        printf("Phone Number: ");
        scanf("%s", phn);
        printf("PIN: ");
        scanf("%d", &pin);

        if (verify_account(phn, pin)) {
            printf(GREEN "\nLogin successful! Welcome!\n" RESET);
            int choice;
            do {
                printf("\n1. Book a Ticket\n2. View Tickets\n3. Cancel Ticket\n4. Logout\nChoose: ");
                scanf("%d", &choice);
                switch (choice) {
                    case 1: book_ticket(phn); break;
                    case 2: view_tickets(phn); break;
                    case 3: cancel_ticket(phn); break;
                    case 4: printf("Logging out...\n"); break;
                    default: printf("Invalid choice!\n");
                }
            } while (choice != 4);
            break;
        } else {
            printf(RED "\nInvalid phone number. Try again.\n" RESET);
            menu();
            break;
        }
    }
}

void sign_up() {
    Account acc;
    int confirm_pin;

    printf(CYAN "\n#### Welcome to Sign Up Section ####\n" RESET);
    printf("First Name: ");
    scanf("%s", acc.F_name);
    printf("Last Name: ");
    scanf("%s", acc.L_name);
    printf("Address: ");
    scanf("%s", acc.address);

    do {
        printf("Phone Number (11 digits): ");
        scanf("%s", acc.phn);
        if (!phone_valid(acc.phn)) {
            printf(RED "Invalid phone number! Must be exactly 11 digits.\n" RESET);
        }
    } while (!phone_valid(acc.phn));

    printf("Create PIN: ");
    scanf("%d", &acc.pin);
    printf("Confirm PIN: ");
    scanf("%d", &confirm_pin);

    pin_check(&acc.pin, &confirm_pin);
    save_account(acc);
    sign_in();
}
void book_ticket(const char *phn) {
    Ticket ticket;
    strcpy(ticket.phn, phn);

    // Location selection
    printf("\nAvailable Locations:\n");
    for (int i = 0; i < TOTAL_LOCATIONS; i++)
        printf("%d. %s\n", i + 1, locations[i]);

    int from, to;
    do {
        printf("From (number 1-%d): ", TOTAL_LOCATIONS);
        scanf("%d", &from);
    } while (from < 1 || from > TOTAL_LOCATIONS);

    do {
        printf("To (number 1-%d): ", TOTAL_LOCATIONS);
        scanf("%d", &to);
        if (to == from) {
            printf(RED "Destination cannot be same as origin. Try again.\n" RESET);
            to = 0;
        }
    } while (to < 1 || to > TOTAL_LOCATIONS);

    strcpy(ticket.from, locations[from - 1]);
    strcpy(ticket.to, locations[to - 1]);

    // Time selection
    printf("\nAvailable Times:\n");
    for (int i = 0; i < TOTAL_TIMES; i++)
        printf("%d. %s\n", i + 1, bus_times[i]);

    int time_choice;
    do {
        printf("Choose Time (1-%d): ", TOTAL_TIMES);
        scanf("%d", &time_choice);
    } while (time_choice < 1 || time_choice > TOTAL_TIMES);

    strcpy(ticket.time, bus_times[time_choice - 1]);

    // Check for available seats
    int bookedSeats[MAX_TICKETS] = {0};
    int seatCount = 0;
    FILE *file = fopen(TICKET_FILE, "r");
    Ticket temp;

    if (file) {
        while (fscanf(file, "%s %s %s %s %s %d %s %d",
                      temp.phn, temp.from, temp.to,
                      temp.time, temp.time + strlen(temp.time),
                      &temp.seatNo, temp.trip_id, &temp.price) == 8) {
            if (strcmp(temp.from, ticket.from) == 0 &&
                strcmp(temp.to, ticket.to) == 0 &&
                strcmp(temp.time, ticket.time) == 0) {
                if (temp.seatNo >= 1 && temp.seatNo <= MAX_TICKETS) {
                    bookedSeats[temp.seatNo - 1] = 1;
                    seatCount++;
                }
            }
        }
        fclose(file);
    }

    if (seatCount >= MAX_TICKETS) {
        printf(RED "\nSorry, all seats are booked for this route and time.\n" RESET);
        return;
    }

    printf("\nAvailable Seats:\n");
    for (int i = 0; i < MAX_TICKETS; i++) {
        if (!bookedSeats[i]) printf("%d ", i + 1);
    }

    do {
        printf("\nChoose Seat (1-%d): ", MAX_TICKETS);
        scanf("%d", &ticket.seatNo);
        if (ticket.seatNo < 1 || ticket.seatNo > MAX_TICKETS || bookedSeats[ticket.seatNo - 1]) {
            printf(RED "Invalid or booked seat. Try again.\n" RESET);
        }
    } while (ticket.seatNo < 1 || ticket.seatNo > MAX_TICKETS || bookedSeats[ticket.seatNo - 1]);

    // Generate trip ID
    generate_trip_id(ticket.trip_id);

    // Price calculation (optional logic)
    ticket.price = 500 + abs(from - to) * 100;

    // Save ticket
    file = fopen(TICKET_FILE, "a");
    if (file) {
        fprintf(file, "%s %s %s %s %d %s %d\n",
                ticket.phn, ticket.from, ticket.to, ticket.time,
                ticket.seatNo, ticket.trip_id, ticket.price);
        fclose(file);

        printf(GREEN "\nTicket booked successfully!\n" RESET);
        printf("Trip ID: %s\n", ticket.trip_id);
        printf("Price: %d BDT\n", ticket.price);
    } else {
        printf(RED "Error saving ticket.\n" RESET);
    }
}

void view_tickets(const char *phn) {
    FILE *file = fopen(TICKET_FILE, "r");
    if (!file) {
        printf(RED "Could not open ticket file.\n" RESET);
        return;
    }

    Ticket t;
    int found = 0, ticketCount = 0;
    const int DEBUG_MODE = 0; // Set 1 to enable debug info

    char search_phn[15];
    strncpy(search_phn, phn, sizeof(search_phn) - 1);
    search_phn[sizeof(search_phn) - 1] = '\0';
    str_trim(search_phn); // Ensure no \n or \r

    if (DEBUG_MODE) {
        printf(CYAN "\n--- DEBUG: Looking for tickets with phone number: '%s' ---\n" RESET, search_phn);
    }

    printf(CYAN "\n--- Your Tickets ---\n" RESET);
    printf("-------------------------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-10s | %-8s | %-4s | %-6s |\n", "Trip ID", "From", "To", "Time", "Seat", "Price");
    printf("-------------------------------------------------------------------------------\n");

    char time1[10], time2[5];

    while (fscanf(file, "%s %s %s %s %s %d %s %d",
                  t.phn, t.from, t.to, time1, time2,
                  &t.seatNo, t.trip_id, &t.price) == 8) {

        snprintf(t.time, sizeof(t.time), "%s %s", time1, time2); // Join time
        str_trim(t.phn); // Clean newline from file data

        if (DEBUG_MODE) {
            printf("DEBUG: Comparing file '%s' with input '%s'\n", t.phn, search_phn);
        }

        if (strcmp(t.phn, search_phn) == 0) {
            ticketCount++;
            printf("| %-10s | %-10s | %-10s | %-8s | %-4d | %-6d |\n",
                   t.trip_id, t.from, t.to, t.time, t.seatNo, t.price);
            found = 1;
        }
    }

    printf("-------------------------------------------------------------------------------\n");
    fclose(file);

    if (!found) {
        printf(RED "\nNo tickets found for this phone number.\n" RESET);
        if (DEBUG_MODE) {
            printf("DEBUG: Check formatting of phone numbers or file entries.\n");
        }
    } else {
        printf(GREEN "\nTotal tickets: %d\n" RESET, ticketCount);
        printf(CYAN "\nNote: Use the Trip ID when canceling a ticket.\n" RESET);
    }
}


void cancel_ticket(const char *phn) {
    char target_id[10];
    int found = 0;

    printf(CYAN "\nEnter Trip ID to cancel (e.g., TRIP0001): " RESET);
    scanf("%s", target_id);

    FILE *file = fopen(TICKET_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        printf(RED "Error accessing ticket files.\n" RESET);
        return;
    }

    Ticket t;
    char time1[10], time2[5];

    while (fscanf(file, "%s %s %s %s %s %d %s %d",
                  t.phn, t.from, t.to, time1, time2,
                  &t.seatNo, t.trip_id, &t.price) == 8) {

        snprintf(t.time, sizeof(t.time), "%s %s", time1, time2);
        str_trim(t.phn);
        str_trim(t.trip_id);

        if (strcmp(t.trip_id, target_id) == 0 && strcmp(t.phn, phn) == 0) {
            found = 1;
            continue; // Skip writing this one = cancel
        }

        // Keep writing other tickets
        fprintf(temp, "%s %s %s %s %s %d %s %d\n",
                t.phn, t.from, t.to, time1, time2, t.seatNo, t.trip_id, t.price);
                  }

    fclose(file);
    fclose(temp);

    // Replace original file
    remove(TICKET_FILE);
    rename("temp.txt", TICKET_FILE);

    if (found) {
        printf(GREEN "\nTicket with Trip ID %s cancelled successfully.\n" RESET, target_id);
    } else {
        printf(RED "\nNo matching ticket found with Trip ID: %s\n" RESET, target_id);
    }
}

void admin_login() {
    int pin;
    printf(CYAN "\nAdmin Login - Enter PIN: " RESET);
    scanf("%d", &pin);

    if (pin == 9999) {
        printf(GREEN "Admin Access Granted.\n" RESET);
        admin_panel();
    }
}

void admin_cancel_ticket_by_trip_id() {
    char target_id[15];
    int found = 0;

    printf(CYAN "\nEnter Trip ID to delete (e.g., TRIP0001): " RESET);
    scanf("%s", target_id);
    str_trim(target_id);

    FILE *file = fopen(TICKET_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file || !temp) {
        printf(RED "Error accessing ticket files.\n" RESET);
        return;
    }

    Ticket t;
    char time1[10], time2[5];

    while (fscanf(file, "%s %s %s %s %s %d %s %d",
                  t.phn, t.from, t.to, time1, time2,
                  &t.seatNo, t.trip_id, &t.price) == 8) {

        snprintf(t.time, sizeof(t.time), "%s %s", time1, time2);
        str_trim(t.trip_id);

        if (strcmp(t.trip_id, target_id) == 0) {
            found = 1;
            continue; // Skip = Delete this
        }

        fprintf(temp, "%s %s %s %s %s %d %s %d\n",
                t.phn, t.from, t.to, time1, time2, t.seatNo, t.trip_id, t.price);
                  }

    fclose(file);
    fclose(temp);

    remove(TICKET_FILE);
    rename("temp.txt", TICKET_FILE);

    if (found) {
        printf(GREEN "\nTicket with Trip ID %s deleted successfully.\n" RESET, target_id);
    } else {
        printf(RED "\nNo ticket found with Trip ID %s.\n" RESET, target_id);
    }
}


void admin_panel() {
    int pin;
    printf(CYAN "\nAdmin Login - Enter PIN: " RESET);
    scanf("%d", &pin);

    if (pin == 9999) {
        printf(GREEN "Admin Access Granted.\n" RESET);

        int option;
        printf("\nAdmin Options:\n");
        printf("1. View All Tickets\n");
        printf("2. Delete Ticket by Trip ID\n");
        printf("3. Return to Main Menu\n");
        printf("Choose: ");
        scanf("%d", &option);

        switch (option) {
            case 1: {
                // View all tickets
                FILE *file = fopen(TICKET_FILE, "r");
                if (!file) {
                    printf(RED "Could not open ticket file.\n" RESET);
                    return;
                }

                Ticket t;
                int ticketCount = 0;
                double totalRevenue = 0;

                printf("\n--- All Booked Tickets ---\n");
                printf("-------------------------------------------------------------------------------------\n");
                printf("| %-8s | %-11s | %-10s | %-10s | %-8s | %-4s | %-7s |\n",
                       "Trip ID", "Phone", "From", "To", "Time", "Seat", "Price");
                printf("-------------------------------------------------------------------------------------\n");

                // Handle both old format and new format with trip_id
                while (1) {
                    // Reset trip_id before each read
                    t.trip_id[0] = '\0';

                    // Try reading with trip_id first
                    int result = fscanf(file, "%s %s %s %s %d %s",
                                      t.phn, t.from, t.to, t.time, &t.seatNo, t.trip_id);

                    // If that fails, try the old format
                    if (result != 6) {
                        // Check if we're at the end of file
                        if (feof(file)) {
                            break;
                        }

                        // Go back to the beginning of the line
                        long pos = ftell(file);
                        if (pos == -1 || fseek(file, pos, SEEK_SET) != 0) {
                            break;  // Error with file position
                        }

                        // Try old format
                        result = fscanf(file, "%s %s %s %s %d",
                                      t.phn, t.from, t.to, t.time, &t.seatNo);

                        if (result != 5) {
                            // Skip this line if we can't read it
                            char buffer[256];
                            if (fgets(buffer, sizeof(buffer), file) == NULL) {
                                break;  // Error or EOF
                            }
                            continue;
                        }
                    }

                    ticketCount++;

                    // Calculate price based on route
                    int from_idx = 0, to_idx = 0;
                    for (int i = 0; i < TOTAL_LOCATIONS; i++) {
                        if (strcmp(t.from, locations[i]) == 0) from_idx = i;
                        if (strcmp(t.to, locations[i]) == 0) to_idx = i;
                    }
                    t.price = 500 + (abs(from_idx - to_idx) * 100);  // Base price + distance factor
                    totalRevenue += t.price;

                    // Display ticket information
                    if (strlen(t.trip_id) > 0) {
                        printf("| %-8s | %-11s | %-10s | %-10s | %-8s | %-4d | %-7d |\n",
                               t.trip_id, t.phn, t.from, t.to, t.time, t.seatNo, t.price);
                    } else {
                        // Auto-generate a trip ID for display
                        char auto_id[10];
                        sprintf(auto_id, "OLD-%04d", ticketCount);

                        printf("| %-8s | %-11s | %-10s | %-10s | %-8s | %-4d | %-7d | (No ID)\n",
                               auto_id, t.phn, t.from, t.to, t.time, t.seatNo, t.price);
                    }
                }

                printf("-------------------------------------------------------------------------------------\n");
                printf("Total Tickets: %d\n", ticketCount);
                printf("Total Revenue: %.2f BDT\n", totalRevenue);

                fclose(file);
                break;
            }
            case 2:
                {
                    admin_cancel_ticket_by_trip_id();
                    break;
                }

            case 3:
                return;

            default:
                printf(RED "Invalid option!\n" RESET);
        }
    } else {
        printf(RED "Access Denied!\n" RESET);
    }
}

void menu() {
    int choice;
    while (1) {
        printf(GREEN "\n############ Welcome to Bus Reservation App ############\n" RESET);
        printf("\n1. Sign In\n2. Sign Up\n3. Admin Panel\n4. Exit\nChoose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: sign_in(); break;
            case 2: sign_up(); break;
            case 3: admin_panel(); break;
            case 4: printf(GREEN "Exiting the system. Goodbye!\n" RESET); exit(0);
            default: printf(RED "Invalid Choice! Try again.\n" RESET);
        }
    }
}

int main() {
    menu();
    return 0;
}
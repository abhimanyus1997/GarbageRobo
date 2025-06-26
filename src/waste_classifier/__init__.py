import os
import sys
import logging
from colorama import init, Fore, Style

# Initialize Colorama to ensure colors work across different terminals
# autoreset=True makes sure that the color resets after each print statement
init(autoreset=True)

# Define a custom formatter to add color based on log level


class ColoredFormatter(logging.Formatter):
    COLORS = {
        logging.DEBUG: Fore.CYAN,
        logging.INFO: Fore.GREEN,
        logging.WARNING: Fore.YELLOW,
        logging.ERROR: Fore.RED + Style.BRIGHT,
        logging.CRITICAL: Fore.MAGENTA + Style.BRIGHT
    }

    def format(self, record):
        color = self.COLORS.get(record.levelno, "")
        message = super().format(record)
        return color + message + Style.RESET_ALL


# Define the logging string format for all messages
# Changed %(module)s to %(name)s for better logger name display
logging_str = "[%(asctime)s] | %(levelname)-8s | %(name)s | Line: %(lineno)d | %(message)s"


# Define the directory where logs will be stored
log_dir = "logs"
# Construct the full path for the log file
log_filepath = os.path.join(log_dir, "running_logs.log")

# Ensure the log directory exists. If not, it will be created.
# exist_ok=True prevents an error if the directory already exists.
os.makedirs(log_dir, exist_ok=True)

# Create a file handler for writing logs to a file
file_handler = logging.FileHandler(log_filepath)
file_handler.setLevel(logging.INFO)  # Set level for file handler
# Use standard formatter for file
file_handler.setFormatter(logging.Formatter(logging_str))

# Create a stream handler for outputting logs to the console
stream_handler = logging.StreamHandler(sys.stdout)
stream_handler.setLevel(logging.INFO)  # Set level for stream handler
# Use custom colored formatter for console
stream_handler.setFormatter(ColoredFormatter(logging_str))

# Configure the root logger with both handlers
logging.basicConfig(
    # Set the default minimum level for messages to be processed (INFO and above)
    level=logging.INFO,
    handlers=[
        file_handler,    # Add the file handler
        stream_handler   # Add the colored stream handler
    ]
)

# This line explicitly creates a logger instance named "wasteClassifierLogger"
# and assigns it to the 'logger' variable within this __init__.py file.
# This makes 'logger' available for direct import from the 'waste_classifier' package.
logger = logging.getLogger("wasteClassifierLogger")


# After basicConfig, any module within the 'waste_classifier' package (or anywhere in your app)
# can get its own logger instance by calling logging.getLogger(__name__).
# This logger will automatically inherit the handlers and formatters defined above.

# Example of how you would use this in another module (e.g., src/waste_classifier/components/data_ingestion.py):
#
# import logging
#
# # Get a logger instance specific to this module.
# # The __name__ variable ensures the logger is named after the module (e.g., 'waste_classifier.components.data_ingestion')
# logger = logging.getLogger(__name__)
#
# def ingest_data():
#     logger.debug("This is a debug message.") # Will not show with INFO level
#     logger.info("Starting data ingestion process...")
#     # ...
#     logger.warning("Potential issue detected during data ingestion.")
#     logger.error("An error occurred during data ingestion!")
#     logger.critical("CRITICAL: Data ingestion has failed completely.")
#     # ...
#     logger.info("Data ingestion completed successfully.")

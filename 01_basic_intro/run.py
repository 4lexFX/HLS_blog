# basic_intro project creation

import vitis
import os

curr_dir = os.getcwd()

# define the variables to make the generic form of this script specific
project_name: str = "basic_intro"
wspc_name: str = "wspc"
cfg_file_loc: str = f"{curr_dir}/hls_config.cfg"
app_template: str = "empty_hls_component"
comp_name: str = "simple_fir"

# derived names/paths
# workspace_path = f"{curr_dir}/{project_name}/{wspc_name}"  # point to where the build is to run
workspace_path = f"{curr_dir}/{wspc_name}"  # point to where the build is to run
print(f"setting the workspace to: {workspace_path}")  # tell the user (debug)

# Initialize session
client = vitis.create_client()
client.set_workspace(path=workspace_path)

# Delete the component if it already exists
if os.path.exists(f"{workspace_path}/{comp_name}"):
	client.delete_component(name=comp_name)

# Create component. Create new config file in the component folder of the workspace
comp = client.create_hls_component(name=comp_name, cfg_file = cfg_file_loc, template = app_template)

# Run flow steps
comp = client.get_component(name=comp_name)
comp.run(operation='C_SIMULATION')
#comp.run(operation='SYNTHESIS')
#comp.run(operation='CO_SIMULATION')

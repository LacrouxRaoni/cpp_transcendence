import React, { useState } from "react";
import './components.css/Login.css'

function Login() {
  	// State to store the username and password
  	const [username, setUsername] = useState('');
  	const [password, setPassword] = useState('');

  	// Function to handle form submission
	 const handleSubmit = (e) => {
    	e.preventDefault();
    	// Perform your authentication logic here
    	console.log('Username:', username);
    	console.log('Password:', password);
    	// You can add authentication logic (e.g., API request) here
	 };
	return(
		<body>
			<h2>Login Page</h2>
			<form onSubmit={handleSubmit}>
	        <div className="form-group">
    	      <label htmlFor="username">Username</label>
         	 <input
            	type="text"
            	id="username"
            	value={username}
            	onChange={(e) => setUsername(e.target.value)}
            	required
	          />
	        </div>
	        <div className="form-group">
      		    <label htmlFor="password">Password</label>
      		    <input
      		      type="password"
      		      id="password"
      		      value={password}
      		      onChange={(e) => setPassword(e.target.value)}
	            required
				/>
				<button type="submit">Login</button>
    		</div>
	      </form>
		</body>
	);
}

export default Login;
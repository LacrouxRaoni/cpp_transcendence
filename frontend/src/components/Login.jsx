import React from "react";
import './components.css/Login.css'

function Login() {
  	// Function to handle submission
	const handleSubmit = (e) => {
    	e.preventDefault();
    	// Perform your authentication logic here
		const authUrl = 'https://api.intra.42.fr/oauth/authorize?client_id=u-s4t2ud-7e3fa4d8bb43bb5f9c0f67832650983a0bbddceecf8c8862f3d73cf917120eb3&redirect_uri=http%3A%2F%2Flocalhost%3A3000%2Fauth-user&response_type=code'
		window.location.href = authUrl

	};
	return(
		<div className="content-login">
			<h2 >Login Page</h2>
			<p>Welcome, cadet, to PongAPI, the awesome game from the last project called 'Transcendence.</p>
			<p>Grab your favorite drink and food, log in, and enjoy the game with fellow cadets. Try to break the record and become the top player in the game.</p>
			<button type="submit" onClick={handleSubmit}>Login</button>
		</div>
	);
}

export default Login;
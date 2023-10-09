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
		const authUrl = 'https://api.intra.42.fr/oauth/authorize?client_id=u-s4t2ud-7e3fa4d8bb43bb5f9c0f67832650983a0bbddceecf8c8862f3d73cf917120eb3&redirect_uri=http%3A%2F%2Flocalhost%3A3000%2Flogin&response_type=code'
		window.location.href = authUrl
		let paramters = new URLSearchParams(window.location.search);
    	let codeParam = paramters.get('code');
		if (codeParam){
			const apiUrl = 'http://localhost:9080/login';
			const dto = {
				key1: 'token',
				key2: codeParam,
			};
			fetch(apiUrl, {
				method: 'POST',
				header: {
					'Content-Type': 'application/json',
				},
				body: JSON.stringify(dto),
			})
			.then(response => {
				if (!response.ok) {
					throw new Error('Network response was not ok');
				  }
				  return response.json(); // Parse the JSON response
				})
				.then(data => {
				  // Handle the API response data
				  console.log(data);
				})
				.catch(error => {
				  // Handle any errors
				  console.error('Error sending POST request:', error);
				});
			};
		};


    	// You can add authentication logic (e.g., API request) here

	return(
		<div className="content-login">
			<h2 >Login Page</h2>
			<p>Welcome, cadet, to PongAPI, the awesome game from the last project called 'Transcendence.</p>
			<p>Grab your favorite drink and food, log in, and enjoy the game with fellow cadets. Try to break the record and become the top player in the game.</p>
			<form onSubmit={handleSubmit}>
			<button type="submit">Login</button>
	      </form>
		</div>
	);
}

export default Login;